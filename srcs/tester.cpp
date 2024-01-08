/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 21:38:52 by maldavid          #+#    #+#             */
/*   Updated: 2024/01/08 00:50:47 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pch.h>
#include <renderer.h>
#include <tests/tester.h>
#include <components/render_results.h>

#if defined(_WIN32) || defined(__CYGWIN__)
	#include <OS/windows/segfault_handler.h>
	#define OS_NAMESPACE windows
#elif defined(__linux__)
	#define MLX_PLAT_LINUX
	#include <OS/unix/segfault_handler.h>
	#define OS_NAMESPACE unix
#elif defined(__APPLE__) && defined(__MACH__)
	#include <OS/unix/segfault_handler.h>
	#define OS_NAMESPACE unix
#elif defined(unix) || defined(__unix__) || defined(__unix)
	#include <OS/unix/segfault_handler.h>
	#define OS_NAMESPACE unix
#else
	#error "Unknown environment (not Windows, not Linux, not MacOS, not Unix)"
#endif

#include <nvidia-flip/FLIP.h>

namespace mlxut
{
	constexpr const double ACCEPTABLE_THRESHOLD = 0.1;
	constexpr const double NEGLIGIBLE_THRESHOLD = 0.001;

	class CoutRedirectGuard
	{
		public:
			CoutRedirectGuard(std::streambuf* new_buffer)  : old(std::cout.rdbuf(new_buffer)) {}
			~CoutRedirectGuard() { std::cout.rdbuf(old); }

		private:
			std::streambuf* old = nullptr;
	};

	class CerrRedirectGuard
	{
		public:
			CerrRedirectGuard(std::streambuf* new_buffer)  : old(std::cerr.rdbuf(new_buffer)) {}
			~CerrRedirectGuard() { std::cerr.rdbuf(old); }

		private:
			std::streambuf* old = nullptr;
	};

	struct SharedMemoryData // shared memory data between forked processes and parent
	{
		Test* test;
		std::size_t* tests_failed;
		std::size_t* tests_passed;
		std::size_t* tests_pending;
		bool* is_running;
	};

	void Tester::createAllTests(const Renderer& renderer)
	{
		for(auto const& dir_entry : std::filesystem::directory_iterator{"./tests/"})
		{
			if(std::filesystem::is_directory(dir_entry.path()))
				continue;
			if(dir_entry.path().extension() != ".lua")
				continue;
			std::string name = dir_entry.path().stem().string();
			std::replace(name.begin(), name.end(), '_', ' ');
			name[0] = std::toupper(name[0]);
			for(int i = 0; i < name.length(); i++)
			{
				if(name[i] != ' ')
					continue;
				if(std::islower(name[i + 1]) != 0)
					name[i + 1] = std::toupper(name[i + 1]);
			}
			std::optional<LuaScript> script = _loader.loadScript(dir_entry.path());
			_tests.emplace_back(std::make_shared<Test>(renderer, script.value(), name));
			_tests_pending++;
			_tests_failed = 0;
			_tests_passed = 0;
		}
	}

	void Tester::runAllTests()
	{
		_tests_pending = 0;
		_tests_failed = 0;
		_tests_passed = 0;
		for(auto& test : _tests)
		{
			test->pend();
			test->setDiffRes(Test::DiffResult::unprocessed);
			_tests_pending++;
		}

		int shm_fd = shm_open("/my_shared_memory", O_CREAT | O_RDWR, 0666);
		ftruncate(shm_fd, sizeof(SharedMemoryData));

		_is_running = true;
		for(auto& test : _tests)
		{
			SharedMemoryData* shared_data = static_cast<SharedMemoryData*>(mmap(NULL, sizeof(SharedMemoryData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0));
			shared_data->test = test.get();
			shared_data->tests_failed = &_tests_failed;
			shared_data->tests_passed = &_tests_passed;
			shared_data->tests_pending = &_tests_pending;
			shared_data->is_running = &_is_running;

			pid_t pid = fork();

			if(pid == -1)
			{
				std::cerr << "failed to fork" << std::endl;
				continue;
			}
			else if(pid == 0)
			{
				testRunner(shared_data);
				std::exit(0);
			}

			munmap(shared_data, sizeof(SharedMemoryData));
		}

		shm_unlink("/my_shared_memory");
	}

	void Tester::testRunner(SharedMemoryData* data)
	{
		OS::OS_NAMESPACE::SegFaultHandler handler;
		data->test->destroyResult();

		std::stringstream buffer;
		CoutRedirectGuard cout_redirection(buffer.rdbuf());
		CerrRedirectGuard cerr_redirection(buffer.rdbuf());

		void* mlx = mlx_init();
		void* render_target = mlx_new_image(mlx, MLX_WIN_WIDTH, MLX_WIN_HEIGHT);
		void* win = mlx_new_window(mlx, MLX_WIN_WIDTH, MLX_WIN_HEIGHT, static_cast<const char*>(render_target));

		data->test->setRenderData(mlx, win);

		data->test->onSetup(mlx, win);

		mlx_loop_hook(mlx, [](void* data) -> int
		{
			Test* test = static_cast<Test*>(data);
			mlx_clear_window(test->_mlx, test->_win);
			test->onUpdate(test->_mlx, test->_win);
			mlx_loop_end(test->_mlx);
			return 0;
		}, data->test);

		mlx_loop(mlx);

		data->test->onQuit(mlx, win);

		mlx_destroy_window(mlx, win);

		// maybe find a better way to retrive texture data :/
		std::vector<uint32_t> pixels;
		for(int y = 0; y < MLX_WIN_HEIGHT; y++)
		{
			for(int x = 0; x < MLX_WIN_WIDTH; x++)
				pixels.push_back(mlx_get_image_pixel(mlx, render_target, x, y));
		}

		mlx_destroy_image(mlx, render_target);
		mlx_destroy_display(mlx);

		Test::DiffResult diff_res = Test::DiffResult::unprocessed;
		if(pixels.size() == data->test->getReferencePixels().size())
		{
			double comp_res = compareImages(pixels, data->test->getReferencePixels());
			if(comp_res < ACCEPTABLE_THRESHOLD)
			{
				if(comp_res < NEGLIGIBLE_THRESHOLD)
					diff_res = Test::DiffResult::negligible;
				else
					diff_res = Test::DiffResult::acceptable;
			}
			else
				diff_res = Test::DiffResult::unacceptable;
		}
		else
			diff_res = Test::DiffResult::unacceptable;

		if(diff_res == Test::DiffResult::unacceptable)
			data->test->failed();

		data->test->setDiffRes(diff_res);
		data->test->setResultPixelsData(std::move(pixels));

		std::string infos = buffer.str();
		data->test->setMLXinfos(infos);
		if(infos.find("[1;31m") != std::string::npos)
			data->test->failed();
		if(data->test->hasScriptFailed())
			data->test->failed();
		if(!data->test->hasFailed())
		{
			data->test->succeeded();
			(*data->tests_passed)++;
		}
		else
			(*data->tests_failed)++;
		(*data->tests_pending)--;
		if(*data->tests_pending == 0)
			*data->is_running = false;
	}

	double Tester::compareImages(const std::vector<uint32_t>& test_res, const std::vector<uint32_t>& ref)
	{

	}
}

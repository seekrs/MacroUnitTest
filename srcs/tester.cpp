/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 21:38:52 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/28 16:43:54 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader/loader.h"
#include "pch.h"
#include <renderer.h>
#include <tests/tester.h>
#include <components/render_results.h>

namespace mlxut
{
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
		for(auto& test : _tests)
		{
			test->pend();
			_tests_pending++;
			_tests_failed = 0;
			_tests_passed = 0;
		}
		_async_holder = std::async(std::launch::async, [this]
		{
			_is_running = true;
			for(auto& test : _tests)
			{
				test->destroyResult();

				std::stringstream buffer;
				CoutRedirectGuard cout_redirection(buffer.rdbuf());
				CerrRedirectGuard cerr_redirection(buffer.rdbuf());

				void* mlx = mlx_init();
				void* render_target = mlx_new_image(mlx, MLX_WIN_WIDTH, MLX_WIN_HEIGHT);
				void* win = mlx_new_window(mlx, MLX_WIN_WIDTH, MLX_WIN_HEIGHT, static_cast<const char*>(render_target));

				test->setRenderData(mlx, win);

				test->onSetup(mlx, win);

				mlx_loop_hook(mlx, [](void* data) -> int
				{
					Test* test = static_cast<Test*>(data);
					mlx_clear_window(test->_mlx, test->_win);
					test->onUpdate(test->_mlx, test->_win);
					mlx_loop_end(test->_mlx);
					return 0;
				}, test.get());

				mlx_loop(mlx);

				test->onQuit(mlx, win);

				mlx_destroy_window(mlx, win);

				// maybe find a better way to retrive texture data :/
				std::vector<uint32_t> pixels;
				for(int y = 0; y < MLX_WIN_HEIGHT; y++)
				{
					for(int x = 0; x < MLX_WIN_WIDTH; x++)
						pixels.push_back(mlx_get_image_pixel(mlx, render_target, x, y));
				}
				test->setResultPixelsData(std::move(pixels));
				mlx_destroy_image(mlx, render_target);
				mlx_destroy_display(mlx);

				std::string infos = buffer.str();
				test->setMLXinfos(infos);
				if(infos.find("[1;31m") != std::string::npos)
					test->failed();
				if(test->hasScriptFailed())
					test->failed();
				if(!test->hasFailed())
				{
					test->succeeded();
					_tests_passed++;
				}
				else
					_tests_failed++;
				_tests_pending--;
			}
			_is_running = false;
		});
	}
}

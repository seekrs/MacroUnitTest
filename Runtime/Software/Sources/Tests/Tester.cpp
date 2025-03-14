#include <Tests/Tester.h>
#include <Core/OS/OSInstance.h>
#include <Graphics/Renderer.h>
#include <Core/Application.h>

#ifdef MLX_UT_EMBED_TESTS
	#include <Embedded/Tests.h>
#endif

namespace mlxut
{
	void Tester::CreateAllTests(const Renderer& renderer)
	{
		#ifndef MLX_UT_EMBED_TESTS
			for(auto const& dir_entry : std::filesystem::directory_iterator{ OSInstance::Get().GetCurrentWorkingDirectoryPath() / "Resources/Tests" })
			{
				if(std::filesystem::is_directory(dir_entry.path()))
					continue;
				if(dir_entry.path().extension() != ".lua")
					continue;
				if(std::find_if(m_tests.begin(), m_tests.end(), [&dir_entry](std::shared_ptr<Test> test) { return test->GetName() == dir_entry.path().stem(); }) != m_tests.end())
					continue;
				m_tests.emplace_back(std::make_shared<Test>(renderer, std::move(dir_entry.path().stem().string())));
				m_tests.back()->CreateRenderTextures();
			}
		#else
			for(const std::string& name : all_test_names)
			{
				m_tests.emplace_back(std::make_shared<Test>(renderer, name));
				m_tests.back()->CreateRenderTextures();
			}
		#endif
		m_pending_tests = m_tests.size();
		std::sort(m_tests.begin(), m_tests.end(), [](std::shared_ptr<Test> rhs, std::shared_ptr<Test> lhs) { return rhs->GetName() < lhs->GetName(); });
	}

	void Tester::RunAllTests(const std::filesystem::path& mlx_path)
	{
		m_pending_tests = m_tests.size();
		for(auto test : m_tests)
			test->Run(mlx_path);
		Application::Get().TestHaveBeenLaunched();
		m_is_running = true;
	}

	void Tester::RunSingleTests(std::size_t index, const std::filesystem::path& mlx_path)
	{
		m_pending_tests = 1;
		m_tests[index]->Run(mlx_path);
		Application::Get().TestHaveBeenLaunched();
		m_is_running = true;
	}

	bool Tester::HaveAllTestsFinished()
	{
		bool all_finished = true;
		for(auto test : m_tests)
		{
			if(!test->IsTestFinished())
			{
				all_finished = false;
				continue;
			}
			if(m_pending_tests > 0)
				m_pending_tests--;
		}
		if(all_finished)
			m_is_running = false;
		return all_finished;
	}

	void Tester::FetchAllResults()
	{
		for(auto test : m_tests)
			test->FetchResult();
	}

	void Tester::CreateAllRenderTextures()
	{
		for(auto test : m_tests)
			test->CreateRenderTextures();
	}

	void Tester::ComputeAllErrorMaps()
	{
		for(auto test : m_tests)
			test->ComputeErrorMap();
	}

	void Tester::FetchSuccess()
	{
		m_passed_tests = 0;
		m_failed_tests = 0;
		m_sus_tests = 0;
		for(auto test : m_tests)
		{
			if(test->HasFailed())
				m_failed_tests++;
			else if(test->IsSuspicious())
				m_sus_tests++;
			else if(test->HasPassed())
				m_passed_tests++;
		}
	}

	void Tester::Reset()
	{
		m_tests.clear();
		m_selected_test = 0;
		m_passed_tests = 0;
		m_failed_tests = 0;
		m_sus_tests = 0;
		m_pending_tests = 0;
		m_is_running = false;
	}
}

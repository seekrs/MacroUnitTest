#include <Tests/Tester.h>
#include <Core/OS/OSInstance.h>
#include <Graphics/Renderer.h>

namespace mlxut
{
	void Tester::CreateAllTests(const Renderer& renderer)
	{
		for(auto const& dir_entry : std::filesystem::directory_iterator{ OSInstance::Get().GetCurrentWorkingDirectoryPath() / "Resources/Tests" })
		{
			if(std::filesystem::is_directory(dir_entry.path()))
				continue;
			if(dir_entry.path().extension() != ".lua")
				continue;
			m_tests.emplace_back(std::make_shared<Test>(renderer, std::move(dir_entry.path().stem().string())));
		}
		m_pending_tests = m_tests.size();
	}

	void Tester::RunAllTests(const std::filesystem::path& mlx_path)
	{
		m_passed_tests = 0;
		m_failed_tests = 0;
		m_pending_tests = 0;
		for(auto test : m_tests)
		{
			test->Run(mlx_path);
		}
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
			if(test->HasFailed())
				m_failed_tests++;
			else if(test->HasPassed())
				m_passed_tests++;
		}
		if(all_finished)
			m_is_running = false;
		return all_finished;
	}
}

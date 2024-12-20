#include "Core/OS/OSInstance.h"
#include <Tests/Test.h>
#include <Graphics/Renderer.h>

namespace mlxut
{
	Test::Test(const class Renderer& renderer, std::string name) :
		m_name(std::move(name)),
		m_renderer(renderer)
	{
	}

	void Test::Reset() noexcept
	{
		m_result_pixels.clear();
		SDL_DestroyTexture(p_result);
		m_logs.clear();
		m_state = TestState::Pending;
	}

	void Test::Run(std::filesystem::path mlx_path)
	{
		p_process.reset();
		p_process = std::make_unique<TinyProcessLib::Process>(
			std::vector<std::string>{
				OSInstance::Get().GetCurrentWorkingDirectoryPath() / "TestRunner",
				"--path=" + std::move(mlx_path).string(),
				m_name
			},
			"",
			[this](const char* bytes, std::size_t n)
			{
				m_logs.append(bytes, n);
			},
			[this](const char* bytes, std::size_t n)
			{
				m_logs.append(bytes, n);
				m_state = TestState::Failed;
			}
		);
		m_state = TestState::Running;
	}

	bool Test::IsTestFinished()
	{
		if(!p_process)
			return true;
		int exit_status;
		if(!p_process->try_get_exit_status(exit_status))
			return false;
		if(exit_status != 0)
			m_state = TestState::Failed;
		return true;
	}
}

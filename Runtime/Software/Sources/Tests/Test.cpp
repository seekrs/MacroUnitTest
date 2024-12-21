#include "Core/OS/OSInstance.h"
#include "PreCompiled.h"
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

	void Test::Run(const std::filesystem::path& mlx_path)
	{
		m_result_pixels.clear();
		m_logs.clear();
		p_process.reset();
		p_process = std::make_unique<TinyProcessLib::Process>(
			std::vector<std::string>{
				OSInstance::Get().GetCurrentWorkingDirectoryPath() / "TestRunner",
				"--script=" + (OSInstance::Get().GetCurrentWorkingDirectoryPath() / "Resources/Tests" / (m_name + ".lua")).string(),
				"--path=" + mlx_path.string(),
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
		if(m_state == TestState::Running)
			m_logs += "\nExit code: " + std::to_string(exit_status);
		if(exit_status != 0)
			m_state = TestState::Failed;
		else if(m_state != TestState::Failed)
			m_state = TestState::Succeeded;
		return true;
	}

	void Test::FetchResult()
	{
		if(m_state == TestState::Running || !m_result_pixels.empty())
			return;

		std::filesystem::path transfer_file_path = std::filesystem::temp_directory_path() / m_name;
		std::ifstream transfer_file(transfer_file_path, std::ios::binary);
		if(!transfer_file.is_open())
		{
			Error("could not open transfer file %", transfer_file_path);
			return;
		}

		transfer_file.seekg(0);
		std::uint32_t part = 0;
		while(transfer_file.read(reinterpret_cast<char*>(&part), sizeof(part)))
			m_result_pixels.push_back(part);
		transfer_file.close();
		std::filesystem::remove(std::move(transfer_file_path));
	}

	void Test::CreateRenderTextures()
	{
		SDL_Surface* surface = nullptr;
		if(!m_result_pixels.empty())
		{
			surface = SDL_CreateRGBSurfaceFrom(m_result_pixels.data(), MLX_WIN_WIDTH, MLX_WIN_HEIGHT, 32, 4 * MLX_WIN_WIDTH, R_MASK, G_MASK, B_MASK, A_MASK);
			p_result = SDL_CreateTextureFromSurface(m_renderer.Get(), surface);
		}
		std::filesystem::path ref_path = OSInstance::Get().GetCurrentWorkingDirectoryPath() / "Resources/Assets/TestsReferences" / (m_name + ".png");
		if(std::filesystem::exists(ref_path))
		{
			if(surface)
				SDL_FreeSurface(surface);
			surface = IMG_Load(ref_path.string().c_str());
			SDL_LockSurface(surface);
			for(int y = 0; y < surface->h; y++)
			{
				for(int x = 0; x < surface->w; x++)
					m_reference_pixels.push_back(*reinterpret_cast<const std::uint32_t*>(reinterpret_cast<const std::uint8_t*>(surface->pixels) + y * surface->pitch + x * surface->format->BytesPerPixel));
			}
			SDL_UnlockSurface(surface);
			p_reference = SDL_CreateTextureFromSurface(m_renderer.Get(), surface);
			SDL_FreeSurface(surface);
		}
		else if(surface)
		{
			IMG_SavePNG(surface, ref_path.string().c_str());
			SDL_FreeSurface(surface);
		}
	}
}

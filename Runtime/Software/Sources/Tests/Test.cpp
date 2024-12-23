#include "PreCompiled.h"
#include <Tests/Test.h>
#include <Graphics/Renderer.h>
#include <Core/OS/OSInstance.h>

#include <FLIP.h>

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
		m_logs += "\nExit code: " + std::to_string(exit_status);
		if(exit_status != 0)
			m_state = TestState::Failed;
		else if(m_state != TestState::Failed)
			m_state = TestState::Succeeded;
		p_process.reset();
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

	void Test::ComputeErrorMap()
	{
		/*
		auto logarithmic_diff = [](std::int16_t diff, std::uint8_t src) -> std::uint8_t
		{
			auto ddiff = std::log2(diff);
			return std::min(255.0, (ddiff * 10.0 + double(src) * 2.0) / 5.0);
		};

		std::vector<std::uint32_t> error_map_data(MLX_WIN_WIDTH * MLX_WIN_HEIGHT);
		for(std::size_t y = 0; y < MLX_WIN_HEIGHT; y++)
		{
			for(std::size_t x = 0; x < MLX_WIN_WIDTH; x++)
			{
				std::uint32_t res_pixel = m_result_pixels[y * MLX_WIN_WIDTH + x];
				std::uint32_t ref_pixel = m_reference_pixels[y * MLX_WIN_WIDTH + x];
				std::uint8_t r = logarithmic_diff((res_pixel >> 24) - (ref_pixel >> 24), (ref_pixel >> 24));
				std::uint8_t g = logarithmic_diff((res_pixel >> 16) - (ref_pixel >> 16), (ref_pixel >> 16));
				std::uint8_t b = logarithmic_diff((res_pixel >>  8) - (ref_pixel >>  8), (ref_pixel >>  8));
				error_map_data[y * MLX_WIN_WIDTH + x] = (r << 24) | (g << 16) | (b << 8) | 0xFF;
			}
		}

		SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(error_map_data.data(), MLX_WIN_WIDTH, MLX_WIN_HEIGHT, 32, 4 * MLX_WIN_WIDTH, R_MASK, G_MASK, B_MASK, A_MASK);
		p_error_map = SDL_CreateTextureFromSurface(m_renderer.Get(), surface);
		SDL_FreeSurface(surface);
		*/

		FLIP::image<FLIP::color3> reference_image;
		{
			std::vector<float> flip_reference_pixels(m_reference_pixels.size() * 3);
			std::size_t i = 0;
			std::for_each(m_reference_pixels.begin(), m_reference_pixels.end(), [&flip_reference_pixels, &i](std::uint32_t pixel)
			{
				flip_reference_pixels[i + 0] = static_cast<std::uint8_t>(pixel >> 24) / 255.0f;
				flip_reference_pixels[i + 1] = static_cast<std::uint8_t>(pixel >> 16) / 255.0f;
				flip_reference_pixels[i + 2] = static_cast<std::uint8_t>(pixel >>  8) / 255.0f;
				i += 3;
			});
			reference_image.setPixels(flip_reference_pixels.data(), MLX_WIN_WIDTH, MLX_WIN_HEIGHT);
		}

		FLIP::image<FLIP::color3> result_image;
		{
			std::vector<float> flip_result_pixels(m_result_pixels.size() * 3);
			std::size_t i = 0;
			std::for_each(m_result_pixels.begin(), m_result_pixels.end(), [&flip_result_pixels, &i](std::uint32_t pixel)
			{
				flip_result_pixels[i + 0] = static_cast<std::uint8_t>(pixel >> 24) / 255.0f;
				flip_result_pixels[i + 1] = static_cast<std::uint8_t>(pixel >> 16) / 255.0f;
				flip_result_pixels[i + 2] = static_cast<std::uint8_t>(pixel >>  8) / 255.0f;
				i += 3;
			});
			result_image.setPixels(flip_result_pixels.data(), MLX_WIN_WIDTH, MLX_WIN_HEIGHT);
		}

		FLIP::image<float> error_map(MLX_WIN_WIDTH, MLX_WIN_HEIGHT, 0.0f);
		FLIP::Parameters parameters{};
		FLIP::evaluate(reference_image, result_image, false, parameters, error_map);

		{
			float sum = 0.0f;
			for(std::size_t y = 0; y < error_map.getHeight(); y++)
			{
				for(std::size_t x = 0; x < error_map.getWidth(); x++)
					sum += error_map.get(x, y);
			}
			m_error_mean = sum / (error_map.getWidth() * error_map.getHeight());
		}

		{
			FLIP::image<FLIP::color3> magma_mapped_image(MLX_WIN_WIDTH, MLX_WIN_HEIGHT);
			magma_mapped_image.colorMap(error_map, FLIP::magmaMap);

			std::vector<std::uint8_t> error_map_data(MLX_WIN_WIDTH * MLX_WIN_HEIGHT * 4);
			auto err_it = error_map_data.begin();
			for(std::size_t y = 0; y < MLX_WIN_HEIGHT; y++)
			{
				for(std::size_t x = 0; x < MLX_WIN_WIDTH; x++)
				{
					FLIP::color3 pixel = magma_mapped_image.getHostData()[y * MLX_WIN_WIDTH + x];
					*err_it = pixel.r * 255.0f; ++err_it;
					*err_it = pixel.g * 255.0f; ++err_it;
					*err_it = pixel.b * 255.0f; ++err_it;
					*err_it = 0xFF; ++err_it;
				}
			}
			SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(error_map_data.data(), MLX_WIN_WIDTH, MLX_WIN_HEIGHT, 32, 4 * MLX_WIN_WIDTH, R_MASK, G_MASK, B_MASK, A_MASK);
			p_error_map = SDL_CreateTextureFromSurface(m_renderer.Get(), surface);
			SDL_FreeSurface(surface);
		}
	}
}

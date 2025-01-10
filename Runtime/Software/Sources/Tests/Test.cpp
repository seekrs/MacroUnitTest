#include <Tests/Test.h>
#include <Graphics/Renderer.h>
#include <Core/OS/OSInstance.h>

#include <FLIP.h>

#ifdef MLX_UT_EMBED_TESTS
	#include <Embedded/References.h>
#endif

namespace mlxut
{
	Test::Test(const class Renderer& renderer, std::string name) :
		m_result_pixels(MLX_WIN_WIDTH * MLX_WIN_HEIGHT, 0),
		m_reference_pixels(MLX_WIN_WIDTH * MLX_WIN_HEIGHT, 0),
		m_name(std::move(name)),
		m_renderer(renderer),
		m_state(TestState::Pending)
	{
	}

	void Test::Reset() noexcept
	{
		std::fill(m_result_pixels.begin(), m_result_pixels.end(), 0);
		SDL_DestroyTexture(p_result);
		p_result = nullptr;
		m_logs.clear();
		m_state = TestState::Pending;
		p_process.reset();
	}

	void Test::DeleteReference()
	{
		std::fill(m_reference_pixels.begin(), m_reference_pixels.end(), 0);
		SDL_DestroyTexture(p_reference);
		p_reference = nullptr;
		#ifndef MLX_UT_EMBED_TESTS
			std::filesystem::remove(OSInstance::Get().GetCurrentWorkingDirectoryPath() / "Resources/Assets/TestsReferences" / (m_name + ".png"));
		#endif
	}

	void Test::Run(const std::filesystem::path& mlx_path)
	{
		Reset();
		p_process = std::make_unique<TinyProcessLib::Process>(
			std::vector<std::string>{
				(OSInstance::Get().GetCurrentWorkingDirectoryPath() / "TestRunner").string(),
				#ifndef MLX_UT_EMBED_TESTS
					"--script-path=" + (OSInstance::Get().GetCurrentWorkingDirectoryPath() / "Resources/Tests" / (m_name + ".lua")).string(),
				#else
					"--script=" + m_name,
				#endif
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
		m_lua_error_message.clear();
		m_lua_line_error = 0;
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
		if(m_state == TestState::Running || m_state == TestState::Pending)
			return;

		std::size_t finder;
		if(HasFailed() && (finder = m_logs.find("Lua Error: ")) != std::string::npos)
		{
			std::string_view line(m_logs.begin() + finder, m_logs.begin() + m_logs.find_first_of('\n', finder));
			finder = line.find_last_of(':');
			if(finder != std::string::npos)
			{
				std::string_view error_line(line.begin() + line.find_last_of(':', finder - 1) + 1, line.begin() + finder);
				if(std::from_chars(error_line.data(), error_line.data() + error_line.size(), m_lua_line_error).ec != std::errc{})
					m_lua_line_error = 0;
				m_lua_error_message = line.substr(finder + 2);
			}
		}

		std::filesystem::path transfer_file_path = std::filesystem::temp_directory_path() / m_name;
		std::ifstream transfer_file(transfer_file_path, std::ios::binary);
		if(!transfer_file.is_open())
			return;

		transfer_file.seekg(0);
		std::uint32_t part = 0;
		std::size_t i = 0;
		while(transfer_file.read(reinterpret_cast<char*>(&part), sizeof(part)))
		{
			m_result_pixels[i] = part;
			i++;
		}
		transfer_file.close();
		std::filesystem::remove(std::move(transfer_file_path));
	}

	void Test::CreateRenderTextures()
	{
		SDL_Surface* surface = nullptr;
		if(m_result_pixels[0] != 0)
		{
			surface = SDL_CreateRGBSurfaceFrom(m_result_pixels.data(), MLX_WIN_WIDTH, MLX_WIN_HEIGHT, 32, 4 * MLX_WIN_WIDTH, R_MASK, G_MASK, B_MASK, A_MASK);
			p_result = SDL_CreateTextureFromSurface(m_renderer.Get(), surface);
		}

		if(p_reference != nullptr)
		{
			if(surface != nullptr)
				SDL_FreeSurface(surface);
			return;
		}

	#ifndef MLX_UT_EMBED_TESTS
		std::filesystem::path ref_path = OSInstance::Get().GetCurrentWorkingDirectoryPath() / "Resources/Assets/TestsReferences" / (m_name + ".png");
		if(std::filesystem::exists(ref_path))
		{
	#endif
			if(surface)
				SDL_FreeSurface(surface);
		#ifndef MLX_UT_EMBED_TESTS
			surface = IMG_Load(ref_path.string().c_str());
		#else
			const auto& ref_data = GetDataFromFilename(m_name);
			SDL_RWops* rw = SDL_RWFromMem(reinterpret_cast<void*>(const_cast<std::uint8_t*>(ref_data.data())), ref_data.size());
			surface = IMG_Load_RW(rw, 1);
		#endif
			SDL_LockSurface(surface);

			auto get_pixel = [](SDL_Surface* surface, int x, int y) -> std::uint32_t
			{
				int bpp = surface->format->BytesPerPixel;
				std::uint8_t* p = reinterpret_cast<std::uint8_t*>(surface->pixels) + y * surface->pitch + x * bpp;

				switch (bpp)
				{
					case 1: return *p; break;
					case 2: return *reinterpret_cast<std::uint16_t*>(p); break;
					case 3:
					{
						if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
							return p[0] << 16 | p[1] << 8 | p[2];
						else
							return p[0] | p[1] << 8 | p[2] << 16;
						break;
					}
					case 4:
					{
						if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
							return p[0] | p[1] << 8 | p[2] << 16 | p[3] << 24;
						else
							return p[0] << 24 | p[1] << 16 | p[2] << 8 | p[3];
						break;
					}

					default: return 0;
				}
			};

			for(std::size_t y = 0; y < MLX_WIN_HEIGHT; y++)
			{
				for(std::size_t x = 0; x < MLX_WIN_WIDTH; x++)
					m_reference_pixels[y * MLX_WIN_WIDTH + x] = get_pixel(surface, x, y);
			}

			SDL_UnlockSurface(surface);
			p_reference = SDL_CreateTextureFromSurface(m_renderer.Get(), surface);
			SDL_FreeSurface(surface);
	#ifndef MLX_UT_EMBED_TESTS
		}
		else if(surface)
		{
			m_reference_pixels = m_result_pixels;
			p_reference = SDL_CreateTextureFromSurface(m_renderer.Get(), surface);
			IMG_SavePNG(surface, ref_path.string().c_str());
			SDL_FreeSurface(surface);
		}
	#endif
	}

	void Test::ComputeErrorMap()
	{
		if(m_state == TestState::Running || m_state == TestState::Pending)
			return;

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
			if(m_error_mean > MEAN_THRESHOLD)
				m_state = TestState::Failed;
			else if(m_error_mean > SUSPICIOUS_THRESHOLD)
				m_state = TestState::Suspicious;
			else if(m_state != TestState::Failed)
				m_state = TestState::Succeeded;
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
					if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
					{
						*err_it = pixel.r * 255.0f; ++err_it;
						*err_it = pixel.g * 255.0f; ++err_it;
						*err_it = pixel.b * 255.0f; ++err_it;
						*err_it = 0xFF; ++err_it;
					}
					else
					{
						*err_it = 0xFF; ++err_it;
						*err_it = pixel.b * 255.0f; ++err_it;
						*err_it = pixel.g * 255.0f; ++err_it;
						*err_it = pixel.r * 255.0f; ++err_it;
					}
				}
			}
			SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(error_map_data.data(), MLX_WIN_WIDTH, MLX_WIN_HEIGHT, 32, 4 * MLX_WIN_WIDTH, R_MASK, G_MASK, B_MASK, A_MASK);
			p_error_map = SDL_CreateTextureFromSurface(m_renderer.Get(), surface);
			SDL_FreeSurface(surface);
		}
	}
}

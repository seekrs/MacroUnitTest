#ifndef MLX_UT_TEST
#define MLX_UT_TEST

#include <Pch.h>
#include <Core/Loader/Loader.h>
#include <SDL/Renderer.h>
#include <Scripting/LuaLcript.h>

namespace mlxut
{
	class Test
	{
		friend class Tester;

		public:
			enum class State
			{
				pending,
				success,
				fail
			};

			enum class DiffResult
			{
				unprocessed,
				negligible,
				acceptable,
				unacceptable
			};

		public:
			Test(const Renderer& renderer, const LuaScript& script, const std::string& name) : _script(script), _name(name)
			{
				std::filesystem::path ref_path("resources/assets/tests_references");
				ref_path /= name + ".png";
				if(!std::filesystem::exists(ref_path))
					return;
				SDL_Surface* surface = IMG_Load(ref_path.string().c_str());
				SDL_LockSurface(surface);
				for(int y = 0; y < surface->h; y++)
				{
					for(int x = 0; x < surface->w; x++)
						_ref_pixels.push_back(*(const uint32_t*)((const char*)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel));
				}
				SDL_UnlockSurface(surface);
				_reference = SDL_CreateTextureFromSurface(renderer.getNativeRenderer(), surface);
				SDL_FreeSurface(surface);
			}

			inline void setRenderData(void* mlx, void* win) noexcept { _mlx = mlx; _win = win;}
			inline void setMLXinfos(const std::string& mlx_infos) { _mlx_infos = mlx_infos; }
			inline void destroyResult() noexcept
			{
				SDL_DestroyTexture(_result);
				_result = nullptr;
				_results_pixels.clear();
			}
			inline void setResultPixelsData(std::vector<uint32_t>&& data) { _results_pixels = data; }

			inline void tryCreateResultTexture(const Renderer& renderer)
			{
				if(_results_pixels.empty())
					return;
				SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(_results_pixels.data(), MLX_WIN_WIDTH, MLX_WIN_HEIGHT, 32, 4 * MLX_WIN_WIDTH, rmask, gmask, bmask, amask);
				_result = SDL_CreateTextureFromSurface(renderer.getNativeRenderer(), surface);
				std::filesystem::path respath = "resources/assets/tests_references";
				respath /= _name + ".png";
				if(!std::filesystem::exists(respath))
					IMG_SavePNG(surface, respath.string().c_str());
				SDL_FreeSurface(surface);
			}

			inline const std::vector<uint32_t>& getReferencePixels() const noexcept { return _ref_pixels; }

			inline constexpr void pend() noexcept { _state = State::pending; }
			inline constexpr void failed() noexcept { _state = State::fail; } 
			inline constexpr void succeeded() noexcept { _state = State::success; } 

			inline SDL_Texture* getResult() const noexcept { return _result; }
			inline SDL_Texture* getReference() const noexcept { return _reference; }

			inline const std::string& getName() const noexcept { return _name; }
			inline const std::string& getMLXinfos() const noexcept { return _mlx_infos; }

			inline bool hasPassed() const noexcept { return _state == State::success; }
			inline bool hasFailed() const noexcept { return _state == State::fail; }
			inline bool isPending() const noexcept { return _state == State::pending; }

			inline void setDiffRes(DiffResult res) noexcept  { _diff_res = res;}
			inline DiffResult getDiffRes() const noexcept { return _diff_res; }

			inline void onSetup(void* mlx, void* win) noexcept { _script.runOnSetup(mlx, win); }
			inline void onUpdate(void* mlx, void* win) noexcept { _script.runOnUpdate(mlx, win); }
			inline void onQuit(void* mlx, void* win) noexcept { _script.runOnQuit(mlx, win); }

			inline bool hasScriptFailed() const noexcept { return _script.failed(); }

			~Test() { destroyResult(); SDL_DestroyTexture(_reference); }

		protected:
			LuaScript _script;
			std::vector<uint32_t> _results_pixels;
			std::vector<uint32_t> _ref_pixels;
			std::string _mlx_infos;
			std::string _name;
			DiffResult _diff_res = DiffResult::unprocessed;
			SDL_Texture* _reference = nullptr;
			SDL_Texture* _result = nullptr;
			void* _mlx = nullptr;
			void* _win = nullptr;
			State _state = State::pending;
	};
}

#endif

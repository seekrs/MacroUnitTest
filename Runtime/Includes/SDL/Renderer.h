#ifndef MLX_UT_RENDERER
#define MLX_UT_RENDERER

#include <Pch.h>

namespace mlxut
{
	class Renderer
	{
		public:
			Renderer(const class Window& win);

			inline SDL_Renderer* const Get() const noexcept { return p_renderer; }
			inline void GetDrawableSize(int& w, int& h) const noexcept { SDL_GetRendererOutputSize(p_renderer, &w, &h); }
			void Destroy() noexcept;

			~Renderer();

		private:
			SDL_Renderer* p_renderer = nullptr;
	};
}

#endif

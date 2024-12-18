#ifndef MLX_UT_RENDERER
#define MLX_UT_RENDERER

#include <PreCompiled.h>
#include <Graphics/Window.h>

namespace mlxut
{
	class Renderer
	{
		public:
			Renderer(const Window& win);

			inline SDL_Renderer* const Get() const noexcept { return p_renderer; }
			inline Vec2i GetDrawableSize() const noexcept { Vec2i v; SDL_GetRendererOutputSize(p_renderer, &v.x, &v.y); return v; }

			~Renderer();

		private:
			SDL_Renderer* p_renderer = nullptr;
	};
}

#endif

#include <Graphics/Renderer.h>

namespace mlxut
{
	Renderer::Renderer(const Window& win)
	{
		p_renderer = SDL_CreateRenderer(win.Get(), -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
		if(!p_renderer)
			FatalError("Unable to create a renderer, %", SDL_GetError());
	}

	Renderer::~Renderer()
	{
		if(p_renderer)
		SDL_DestroyRenderer(p_renderer);
	}
}

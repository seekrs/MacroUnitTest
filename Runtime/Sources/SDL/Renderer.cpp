#include <renderer.h>
#include <window.h>
#include <errors.h>

namespace mlxut
{
	Renderer::Renderer(const Window& win)
	{
		_renderer = SDL_CreateRenderer(win.getNativeWindow(), -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
		if(!_renderer)
			core::error::report(e_kind::fatal_error, std::string("unable to create a renderer, ") + SDL_GetError());
	}

	void Renderer::destroy() noexcept
	{
		if(_renderer == nullptr)
			return;
		SDL_DestroyRenderer(_renderer);
		_renderer = nullptr;
	}

	Renderer::~Renderer()
	{
		destroy();
	}
}

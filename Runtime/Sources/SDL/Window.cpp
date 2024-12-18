#include <window.h>
#include <icon.h>
#include <errors.h>

namespace mlxut
{
	Window::Window(const std::string& title, std::size_t w, std::size_t h)
	{
		_win = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS);
		if(!_win)
			core::error::report(e_kind::fatal_error, std::string("unable to open a new window, ") + SDL_GetError());
		_icon = SDL_CreateRGBSurfaceFrom(static_cast<void*>(logo_mlx), logo_mlx_width, logo_mlx_height, 32, 4 * logo_mlx_width, rmask, gmask, bmask, amask);
		SDL_SetWindowIcon(_win, _icon);
		SDL_SetWindowMinimumSize(_win, 128, 75);
	}

	void Window::destroy() noexcept
	{
		if(_win != nullptr)
		{
			SDL_DestroyWindow(_win);
			_win = nullptr;
		}
		if(_icon == nullptr)
		{
			SDL_FreeSurface(_icon);
			_icon = nullptr;
		}
	}

	Window::~Window()
	{
		destroy();
	}
}

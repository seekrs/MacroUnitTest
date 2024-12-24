#include <Graphics/Window.h>
#include <Core/Icon.h>

namespace mlxut
{
	SDL_HitTestResult HitTestCallback(SDL_Window* win, const SDL_Point* area, [[maybe_unused]] void* data)
	{
		int w, h;
		SDL_GetWindowSize(win, &w, &h);
		if(area->y < RESIZE_MARGIN && area->x > 275 && area->x < w - 95)
		{
			if(area->x < RESIZE_MARGIN)
				return SDL_HITTEST_RESIZE_TOPLEFT;
			if(area->x > w - RESIZE_MARGIN)
				return SDL_HITTEST_RESIZE_TOPRIGHT;
			return SDL_HITTEST_RESIZE_TOP;
		}
		if(area->y < 25 && area->x > 275 && area->x < w - 95)
			return SDL_HITTEST_DRAGGABLE;
		if(area->y > h - RESIZE_MARGIN)
		{
			if(area->x < RESIZE_MARGIN)
				return SDL_HITTEST_RESIZE_BOTTOMLEFT;
			if(area->x > w - RESIZE_MARGIN)
				return SDL_HITTEST_RESIZE_BOTTOMRIGHT;
			return SDL_HITTEST_RESIZE_BOTTOM;
		}
		if(area->x < RESIZE_MARGIN)
			return SDL_HITTEST_RESIZE_LEFT;
		if(area->x > w - RESIZE_MARGIN)
			return SDL_HITTEST_RESIZE_RIGHT;
		return SDL_HITTEST_NORMAL;
	}

	Window::Window(std::string title, std::size_t w, std::size_t h)
	{
		p_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS);
		if(!p_window)
			FatalError("Unable to open a window, %", SDL_GetError());
		p_icon = SDL_CreateRGBSurfaceFrom(static_cast<void*>(logo_mlx), logo_mlx_width, logo_mlx_height, 32, 4 * logo_mlx_width, R_MASK, G_MASK, B_MASK, A_MASK);
		SDL_SetWindowIcon(p_window, p_icon);
		SDL_SetWindowMinimumSize(p_window, 128, 75);
		SDL_SetWindowHitTest(p_window, HitTestCallback, nullptr);
	}

	Window::~Window()
	{
		if(p_window != nullptr)
			SDL_DestroyWindow(p_window);
		if(p_icon == nullptr)
			SDL_FreeSurface(p_icon);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:36:51 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/19 17:11:46 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <window.h>
#include <icon.h>
#include <errors.h>

namespace mlxut
{
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		constexpr const std::uint32_t rmask = 0xff000000;
		constexpr const std::uint32_t gmask = 0x00ff0000;
		constexpr const std::uint32_t bmask = 0x0000ff00;
		constexpr const std::uint32_t amask = 0x000000ff;
	#else
		constexpr const std::uint32_t rmask = 0x000000ff;
		constexpr const std::uint32_t gmask = 0x0000ff00;
		constexpr const std::uint32_t bmask = 0x00ff0000;
		constexpr const std::uint32_t amask = 0xff000000;
	#endif

	Window::Window(const std::string& title, std::size_t w, std::size_t h)
	{
		_win = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if(!_win)
			core::error::report(e_kind::fatal_error, std::string("unable to open a new window, ") + SDL_GetError());
		_icon = SDL_CreateRGBSurfaceFrom(static_cast<void*>(logo_mlx), logo_mlx_width, logo_mlx_height, 32, 4 * logo_mlx_width, rmask, gmask, bmask, amask);
		SDL_SetWindowIcon(_win, _icon);
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

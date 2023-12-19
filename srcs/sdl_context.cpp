/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_context.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:19:27 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/19 20:38:30 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sdl_context.h>
#include <errors.h>
#include <pch.h>

#if !SDL_VERSION_ATLEAST(2, 0, 17)
	#error "ImGui requires SDL 2.0.17+ because of SDL_RenderGeometry() function"
#endif

namespace mlxut
{
	SDLContext::SDLContext()
	{
		if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
			core::error::report(e_kind::fatal_error, std::string("unable to init the SDL, ") + SDL_GetError());

		#ifdef SDL_HINT_IME_SHOW_UI
		SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
		#endif
	}

	SDLContext::~SDLContext()
	{
		SDL_Quit();
	}
}

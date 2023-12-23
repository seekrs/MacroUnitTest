/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pch.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:59:08 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/23 00:03:21 by kbz_8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_PCH__
#define __MLX_UT_PCH__

#include <vector>
#include <array>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdarg>
#include <cstdint>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <memory>

#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vec2.h>

constexpr const uint16_t WINDOW_WIDTH = 1280;
constexpr const uint16_t WINDOW_HEIGHT = 750;

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

#endif

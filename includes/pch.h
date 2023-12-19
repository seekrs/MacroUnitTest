/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pch.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:59:08 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/19 16:53:24 by maldavid         ###   ########.fr       */
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
#include <utility>

#include <SDL2/SDL.h>

#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>

constexpr const uint16_t WINDOW_WIDTH = 1280;
constexpr const uint16_t WINDOW_HEIGHT = 750;

#endif

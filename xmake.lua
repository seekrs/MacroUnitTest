-- **************************************************************************** --
--                                                                              --
--                                                         :::      ::::::::    --
--    xmake.lua                                          :+:      :+:    :+:    --
--                                                     +:+ +:+         +:+      --
--    By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+         --
--                                                 +#+#+#+#+#+   +#+            --
--    Created: 2023/12/19 14:51:42 by maldavid          #+#    #+#              --
--    Updated: 2023/12/19 14:51:42 by maldavid         ###   ########.fr        --
--                                                                              --
-- **************************************************************************** --

add_requires("imgui v1.90-docking", { configs = { sdl2 = true }})
add_requires("libsdl", "libsdl_image")

add_rules("mode.debug", "mode.release")
set_languages("cxx17")

set_objectdir("build/objects/$(os)_$(arch)")
set_targetdir("build/$(os)_$(arch)")

set_optimize("fastest")

target("MacroUnitTest")
	set_default(true)
	set_license("MIT")
	set_kind("binary")
	
	set_targetdir("./")

	add_packages("libsdl", "libsdl_image", "imgui")

	add_includedirs("includes", "srcs")

	add_files("srcs/**.cpp")

	set_pcxxheader("includes/pch.h")

	add_defines("SDL_MAIN_HANDLED")

	if is_mode("debug") then
		add_defines("MLX_UT_DEBUG")
	elseif is_mode("release") then
		add_defines("MLX_UT_RELEASE")
	end
target_end()

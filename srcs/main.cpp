/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:04:27 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/19 17:50:31 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pch.h>
#include <window.h>
#include <renderer.h>
#include <imgui_context.h>
#include <sdl_context.h>
#include <components/main_menu_bar.h>

int main()
{
	mlxut::SDLContext sdl_context;
	mlxut::Window win("MacroLibX Unit Tester", WINDOW_WIDTH, WINDOW_HEIGHT);
	mlxut::Renderer renderer(win);
	mlxut::ImGuiContext imgui(win, renderer);
	mlxut::MainMenuBar menubar;

	for(;;)
	{
		if(!imgui.checkEvents())
			break;
		imgui.beginFrame();
		menubar.render();
		imgui.endFrame();
	}

	imgui.destroy();
	renderer.destroy();
	win.destroy();
	return 0;
}

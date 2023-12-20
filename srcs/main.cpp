/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:04:27 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/20 02:16:22 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pch.h>
#include <window.h>
#include <renderer.h>
#include <imgui_context.h>
#include <sdl_context.h>
#include <components/main_menu_bar.h>
#include <components/panel_stack.h>
#include <components/render_results.h>
#include <components/mlx_infos.h>
#include <components/tests_list.h>
#include <components/test_stats.h>
#include <components/docks.h>

int main()
{
	mlxut::SDLContext sdl_context;
	mlxut::Window win("MacroLibX Unit Tester", WINDOW_WIDTH, WINDOW_HEIGHT);
	mlxut::Renderer renderer(win);
	mlxut::ImGuiContext imgui(win, renderer);
	mlxut::MainMenuBar menubar;

	mlxut::Docks docks;
	mlxut::TestList test_list;
	mlxut::TestStats test_stats;
	mlxut::RenderResults render_results;
	mlxut::MLXinfos mlx_infos;

	mlxut::PanelStack stack;
	stack.addPanel(&docks);
	stack.addPanel(&test_list);
	stack.addPanel(&render_results);
	stack.addPanel(&mlx_infos);
	stack.addPanel(&test_stats);

	for(;;)
	{
		if(!imgui.checkEvents())
			break;
		if(menubar.quitRequested())
			break;
		imgui.beginFrame();

		mlxut::ivec2 size;
		renderer.getDrawableSize(size.x, size.y);

		menubar.render(size);

		for(mlxut::Panel* const panel : stack.getPanels())
			panel->onUpdate(size);

		if(menubar.shouldRenderAboutWindow())
			menubar.renderAboutWindow(size);

		imgui.endFrame();
	}

	imgui.destroy();
	renderer.destroy();
	win.destroy();
	return 0;
}

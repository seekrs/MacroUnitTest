/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:04:27 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/22 22:46:31 by kbz_8            ###   ########.fr       */
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
#include <loader/loader.h>
#include <tests/tester.h>

SDL_HitTestResult hitTestCallback(SDL_Window* win, const SDL_Point* area, [[maybe_unused]] void* data);
void cursorUpdate(const mlxut::Window& window) noexcept;
void loadCursors() noexcept;

int main()
{
	mlxut::SDLContext sdl_context;
	mlxut::Window win("MacroLibX Unit Tester", WINDOW_WIDTH, WINDOW_HEIGHT);
	mlxut::Renderer renderer(win);
	mlxut::ImGuiContext imgui(win, renderer);
	mlxut::MainMenuBar menubar(renderer);

	mlxut::Docks docks;
	mlxut::TestList test_list;
	mlxut::TestStats test_stats;
	mlxut::RenderResults render_results;
	mlxut::MLXinfos mlx_infos;
	mlxut::Tester tester;

	mlxut::PanelStack stack;
	stack.addPanel(&docks);
	stack.addPanel(&test_list);
	stack.addPanel(&render_results);
	stack.addPanel(&mlx_infos);
	stack.addPanel(&test_stats);

	loadCursors();
	SDL_SetWindowHitTest(win.getNativeWindow(), hitTestCallback, nullptr);

	if(mlxut::loadMLX())
	{
		for(;;)
		{
			if(!imgui.checkEvents())
				break;
			if(menubar.quitRequested())
				break;
			imgui.beginFrame();

			mlxut::ivec2 size;
			renderer.getDrawableSize(size.x, size.y);

			menubar.render(win, size);

			for(mlxut::Panel* const panel : stack.getPanels())
				panel->onUpdate(size);

			if(menubar.shouldRenderAboutWindow())
				menubar.renderAboutWindow(size);

			imgui.endFrame();

			cursorUpdate(win);

			if(menubar.runAllTestsRequest())
				tester.runAllTests(renderer, render_results);
		}
		mlxut::unloadMLX();
	}

	menubar.destroy();
	imgui.destroy();
	renderer.destroy();
	win.destroy();
	return 0;
}

static std::unordered_map<SDL_SystemCursor, SDL_Cursor*> cursors;
constexpr const int RESIZE_MARGIN = 5;

void loadCursors() noexcept
{
	cursors[SDL_SYSTEM_CURSOR_ARROW] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	cursors[SDL_SYSTEM_CURSOR_IBEAM] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
	cursors[SDL_SYSTEM_CURSOR_WAIT] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAIT);
	cursors[SDL_SYSTEM_CURSOR_CROSSHAIR] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
	cursors[SDL_SYSTEM_CURSOR_WAITARROW] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAITARROW);
	cursors[SDL_SYSTEM_CURSOR_SIZENWSE] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENWSE);
	cursors[SDL_SYSTEM_CURSOR_SIZENESW] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENESW);
	cursors[SDL_SYSTEM_CURSOR_SIZEWE] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
	cursors[SDL_SYSTEM_CURSOR_SIZENS] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
	cursors[SDL_SYSTEM_CURSOR_SIZEALL] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
	cursors[SDL_SYSTEM_CURSOR_NO] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NO);
	cursors[SDL_SYSTEM_CURSOR_HAND] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
}

SDL_HitTestResult hitTestCallback(SDL_Window* win, const SDL_Point* area, [[maybe_unused]] void* data)
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

void cursorUpdate(const mlxut::Window& win) noexcept
{
	int w, h;
	SDL_GetWindowSize(win.getNativeWindow(), &w, &h);
	int x, y;
	SDL_GetMouseState(&x, &y);
	if(y < RESIZE_MARGIN && x > 275 && x < w - 95)
	{
		if(x < RESIZE_MARGIN)
			SDL_SetCursor(cursors[SDL_SYSTEM_CURSOR_SIZENWSE]);
		else if(x > w - RESIZE_MARGIN)
			SDL_SetCursor(cursors[SDL_SYSTEM_CURSOR_SIZENESW]);
		else
			SDL_SetCursor(cursors[SDL_SYSTEM_CURSOR_SIZENS]);
	}
	else if(y > h - RESIZE_MARGIN)
	{
		if(x < RESIZE_MARGIN)
			SDL_SetCursor(cursors[SDL_SYSTEM_CURSOR_SIZENESW]);
		else if(x > w - RESIZE_MARGIN)
			SDL_SetCursor(cursors[SDL_SYSTEM_CURSOR_SIZENWSE]);
		else
			SDL_SetCursor(cursors[SDL_SYSTEM_CURSOR_SIZENS]);
	}
	else if(x < RESIZE_MARGIN)
		SDL_SetCursor(cursors[SDL_SYSTEM_CURSOR_SIZEWE]);
	else if(x > w - RESIZE_MARGIN)
		SDL_SetCursor(cursors[SDL_SYSTEM_CURSOR_SIZEWE]);
	else
		SDL_SetCursor(cursors[SDL_SYSTEM_CURSOR_ARROW]);
}

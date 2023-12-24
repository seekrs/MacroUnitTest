/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu_bar.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:47:01 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/23 19:49:35 by kbz_8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <components/main_menu_bar.h>
#include <imgui.h>
#include <renderer.h>
#include <window.h>
#include <material_font.h>

namespace mlxut
{
	MainMenuBar::MainMenuBar(const Renderer& renderer)
	{
		_logo = IMG_LoadTexture(renderer.getNativeRenderer(), "./resources/assets/logo.png");
	}

	void MainMenuBar::render(const Window& win, ivec2 size) noexcept
	{
		_run_all_tests_requested = false;

		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.f, 0.f, 0.f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0.f, 0.f, 0.f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.19f, 0.19f, 0.19f, 0.54f));

			if(!ImGui::BeginMainMenuBar())
				return;
			ImGui::Image(static_cast<void*>(_logo), ImVec2(20, 20));
			if(ImGui::Button("Launch all tests"))
				_run_all_tests_requested = true;
			if(ImGui::BeginMenu("Help"))
			{
				if(ImGui::MenuItem("About"))
					_render_about_window = true;
				ImGui::EndMenu();
			}
			ImGui::SameLine(static_cast<float>(size.x) / 2.0f - ImGui::CalcTextSize("MacroLibX Unit Tester").x / 2.0f);
			ImGui::TextUnformatted("MacroLibX Unit Tester");
			ImGui::SameLine(size.x - 100);
			if(ImGui::Button(MLXUT_ICON_MD_REMOVE))
				SDL_MinimizeWindow(win.getNativeWindow());
			bool maximized = (SDL_GetWindowFlags(win.getNativeWindow()) & SDL_WINDOW_MAXIMIZED);
			if(ImGui::Button(maximized ? MLXUT_ICON_MD_FULLSCREEN_EXIT : MLXUT_ICON_MD_FULLSCREEN))
			{
				if(maximized)
					SDL_RestoreWindow(win.getNativeWindow());
				else
					SDL_MaximizeWindow(win.getNativeWindow());
			}
			if(ImGui::Button(MLXUT_ICON_MD_CLOSE))
				_quit_requested = true;
			ImGui::EndMainMenuBar();

		ImGui::PopStyleColor(4);
	}

	void MainMenuBar::renderAboutWindow(ivec2 size)
	{
		if(!ImGui::Begin("About", &_render_about_window, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_HorizontalScrollbar))
			return;

		ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() / 2 - 128, ImGui::GetWindowHeight() / 8));
		ImGui::Image(static_cast<void*>(_logo), ImVec2(255, 255));

		ImGui::End();
	}

	void MainMenuBar::destroy() noexcept
	{
		if(_logo == nullptr)
			return;
		SDL_DestroyTexture(_logo);
		_logo = nullptr;
	}

	MainMenuBar::~MainMenuBar()
	{
		destroy();
	}
}

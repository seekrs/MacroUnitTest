/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu_bar.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:47:01 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/20 02:29:36 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <components/main_menu_bar.h>
#include <renderer.h>

namespace mlxut
{
	MainMenuBar::MainMenuBar(const Renderer& renderer)
	{
		_logo = IMG_LoadTexture(renderer.getNativeRenderer(), "./resources/assets/logo.png");
	}

	void MainMenuBar::render(ivec2 size) noexcept
	{
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.f, 0.f, 0.f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0.f, 0.f, 0.f, 1.f));

			if(!ImGui::BeginMainMenuBar())
				return;
			ImGui::Image(static_cast<void*>(_logo), ImVec2(20, 20));
			if(ImGui::BeginMenu("Help"))
			{
				if(ImGui::MenuItem("About"))
					_render_about_window = true;
				ImGui::EndMenu();
			}
			ImGui::SameLine(size.x - 25);
			if(ImGui::Button("X"))
				_quit_requested = true;
			ImGui::EndMainMenuBar();

		ImGui::PopStyleColor(3);
	}

	void MainMenuBar::renderAboutWindow(ivec2 size)
	{
		if(!ImGui::Begin("About", &_render_about_window, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_HorizontalScrollbar))
			return;

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu_bar.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:47:01 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/20 02:15:14 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <components/main_menu_bar.h>

namespace mlxut
{
	void MainMenuBar::render(ivec2 size) noexcept
	{
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.f, 0.f, 0.f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0.f, 0.f, 0.f, 1.f));

			if(!ImGui::BeginMainMenuBar())
				return;
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
}

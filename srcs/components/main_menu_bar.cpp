/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu_bar.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:47:01 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/20 00:03:32 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <components/main_menu_bar.h>

namespace mlxut
{
	void MainMenuBar::render(ivec2 size) noexcept
	{
		if(!ImGui::BeginMainMenuBar())
			return;
		if(ImGui::BeginMenu("Help"))
		{
			if(ImGui::MenuItem("About"))
				_render_about_window = true;
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();

		if(_render_about_window)
			renderAboutWindow(size);
	}

	void MainMenuBar::renderAboutWindow(ivec2 size)
	{
		if(!ImGui::Begin("About", &_render_about_window, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_HorizontalScrollbar))
			return;

		ImGui::End();
	}
}

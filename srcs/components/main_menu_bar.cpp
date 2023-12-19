/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu_bar.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:47:01 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/19 18:08:39 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <components/main_menu_bar.h>

namespace mlxut
{
	void MainMenuBar::render() noexcept
	{
		if(!ImGui::BeginMainMenuBar())
			return;
		if(ImGui::BeginMenu("Help"))
		{
			if(ImGui::MenuItem("About"))
			{
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   docks.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 21:41:41 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/20 00:31:59 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <components/docks.h>

namespace mlxut
{
	Docks::Docks() : Panel("docks") {}

	void Docks::onUpdate(ivec2 size)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGui::SetNextWindowPos({static_cast<float>(size.x) / 4 + 1, 20});
		ImGui::SetNextWindowSize({static_cast<float>(size.x) / 2, static_cast<float>(size.y) / 1.5f});
		if(ImGui::Begin("CentralDockSpaceWindow", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking))
		{
			ImGuiID dockspace_id = ImGui::GetID("CentralDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoWindowMenuButton);

			// for wathever reason I need to do the docking part two times for it to work :/
			static int first_times_docks = 0;
			if(first_times_docks < 2)
			{
				ImGui::DockBuilderRemoveNode(dockspace_id);
				ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_DockSpace | ImGuiDockNodeFlags_NoWindowMenuButton);

				ImGui::DockBuilderDockWindow("Render Results", dockspace_id);
				ImGui::DockBuilderDockWindow("About", dockspace_id);

				ImGui::DockBuilderFinish(dockspace_id);

				first_times_docks++;
			}
			ImGui::End();
		}

		ImGui::PopStyleVar();
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_results.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:26:29 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/20 00:01:22 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <components/render_results.h>

namespace mlxut
{
	RenderResults::RenderResults() : Panel("render_results") {}

	void RenderResults::onUpdate(ivec2 size)
	{
		if(!ImGui::Begin("Render Results", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
			return;

		ImGui::End();
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_results.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:26:29 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/24 16:21:00 by kbz_8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <components/render_results.h>
#include <tests/tester.h>

namespace mlxut
{
	RenderResults::RenderResults(Tester* tester) : Panel("render_results"), _tester(tester) {}

	void RenderResults::onUpdate(ivec2 size)
	{
		if(!ImGui::Begin("Render Results", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
			return;
		ImGui::TextUnformatted(_tester->getAllTests()[_tester->getActiveTestIndex()]->getName().c_str());
		if(!_textures.empty())
			ImGui::Image(static_cast<void*>(_textures[_tester->getActiveTestIndex()]), {400, 400});
		ImGui::End();
	}
}

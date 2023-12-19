/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_infos.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:33:11 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/19 23:28:48 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <components/mlx_infos.h>

namespace mlxut
{
	MLXinfos::MLXinfos() : Panel("mlx_infos") {}

	void MLXinfos::onUpdate(ivec2 size)
	{
		ImGui::SetNextWindowPos({static_cast<float>(size.x) / 2 + static_cast<float>(size.x) / 4 + 1, 20});
		ImGui::SetNextWindowSize({static_cast<float>(size.x) / 4 - 2, static_cast<float>(size.y) - 21});
		if(!ImGui::Begin("MLX Infos", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus))
			return;

		ImGui::End();
	}
}

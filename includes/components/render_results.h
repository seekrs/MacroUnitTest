/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_results.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:25:23 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/22 22:49:49 by kbz_8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_RENDER_RESULTS__
#define __MLX_UT_RENDER_RESULTS__

#include <pch.h>
#include <components/panel.h>

namespace mlxut
{
	class RenderResults : public Panel
	{
		public:
			RenderResults();
			void onUpdate(ivec2 size) override;
			inline void addResult(SDL_Texture* texture) noexcept { _textures.push_back(texture); }
			inline void destroy() noexcept { std::for_each(_textures.begin(), _textures.end(), [](SDL_Texture* texture)
											{
												SDL_DestroyTexture(texture);
											}); }
			~RenderResults() override = default;

		private:
			std::vector<SDL_Texture*> _textures;
	};
}

#endif

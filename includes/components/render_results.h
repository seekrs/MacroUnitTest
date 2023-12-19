/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_results.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:25:23 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/19 19:26:08 by maldavid         ###   ########.fr       */
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
			~RenderResults() override = default;
	};
}

#endif

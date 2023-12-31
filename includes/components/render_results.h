/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_results.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:25:23 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/28 12:29:55 by maldavid         ###   ########.fr       */
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
			RenderResults(class Tester* tester, const class Renderer& renderer);
			void onUpdate(ivec2 size) override;
			~RenderResults() override = default;

		private:
			const class Renderer& _renderer;
			class Tester* _tester = nullptr;
	};
}

#endif

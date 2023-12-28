/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_infos.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:32:26 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/28 02:07:46 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_MLX_INFOS__
#define __MLX_UT_MLX_INFOS__

#include <pch.h>
#include <components/panel.h>

namespace mlxut
{
	class MLXinfos : public Panel
	{
		public:
			MLXinfos(class Tester* tester);
			void onUpdate(ivec2 size) override;
			~MLXinfos() override = default;

		private:
			class Tester* _tester = nullptr;
	};
}

#endif

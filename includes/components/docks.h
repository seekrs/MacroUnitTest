/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   docks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 21:40:02 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/28 02:07:53 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_DOCKS__
#define __MLX_UT_DOCKS__

#include <pch.h>
#include <components/panel.h>

namespace mlxut
{
	class Docks : public Panel
	{
		public:
			Docks();
			void onUpdate(ivec2 size) override;
			~Docks() override = default;
	};
}

#endif

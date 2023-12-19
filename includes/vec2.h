/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:11:51 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/19 19:13:09 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_VEC2__
#define __MLX_UT_VEC2__

namespace mlxut
{
	struct ivec2
	{
		int x;
		int y;

		constexpr ivec2() : x(0), y(0) {}
		constexpr ivec2(int _x, int _y) : x(_x), y(_y) {}
	};
}

#endif

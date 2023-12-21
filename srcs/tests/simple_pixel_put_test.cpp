/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_pixel_put_test.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 21:26:54 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/22 00:20:56 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tests/simple_pixel_put_test.h>

namespace mlxut
{
	void SimplePixelPutTest::run()
	{
		for(int y = 0; y < 40; y++)
		{
			for(int x = 0; x < 40; x++)
				mlx_pixel_put(_mlx, _win, x, y, 0xFFFF0000);
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_pixel_put_test.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:20:17 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/21 22:00:13 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_SIMPLE_PIXEL_PUT_TEST__
#define __MLX_UT_SIMPLE_PIXEL_PUT_TEST__

#include <tests/base_test.h>

namespace mlxut
{
	class SimplePixelPutTest : public BaseTest
	{
		public:
			SimplePixelPutTest(void* mlx, void* win) : BaseTest(mlx, win) {}
			void run() override;
			~SimplePixelPutTest() override = default;
	};
}

#endif

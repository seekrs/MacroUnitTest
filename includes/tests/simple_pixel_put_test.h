/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_pixel_put_test.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:20:17 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/25 14:20:04 by kbz_8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_SIMPLE_PIXEL_PUT_TEST__
#define __MLX_UT_SIMPLE_PIXEL_PUT_TEST__

#include <tests/base_test.h>

namespace mlxut
{
	class SimplePixelPutTest final : public BaseTest
	{
		public:
			SimplePixelPutTest(const Renderer& renderer) : BaseTest(renderer, "Simple Pixel Put") {}
			void run() override;
			~SimplePixelPutTest() override = default;
	};
}

#endif

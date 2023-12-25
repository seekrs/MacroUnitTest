/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_image_put_test.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbz_8 </var/spool/mail/kbz_8>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 20:56:31 by kbz_8             #+#    #+#             */
/*   Updated: 2023/12/25 15:45:12 by kbz_8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_MULTIPLE_IMAGE_PUT_TEST__
#define __MLX_UT_MULTIPLE_IMAGE_PUT_TEST__

#include <tests/base_test.h>

namespace mlxut
{
	class MultipleImagePutTest final : public BaseTest
	{
		public:
			MultipleImagePutTest(const Renderer& renderer) : BaseTest(renderer, "Multiple Image Put") {}
			void setup() override;
			void run() override;
			void cleanup() override;
			~MultipleImagePutTest() override = default;

		private:
			void* _image = nullptr;
			int _w;
			int _h;
	};
}

#endif

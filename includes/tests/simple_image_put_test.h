/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_image_put_test.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbz_8 </var/spool/mail/kbz_8>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 20:56:31 by kbz_8             #+#    #+#             */
/*   Updated: 2023/12/24 17:02:39 by kbz_8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_SIMPLE_IMAGE_PUT_TEST__
#define __MLX_UT_SIMPLE_IMAGE_PUT_TEST__

#include <tests/base_test.h>

namespace mlxut
{
	class SimpleImagePutTest final : public BaseTest
	{
		public:
			SimpleImagePutTest() : BaseTest("Simple Image Put") {}
			void setup() override;
			void run() override;
			void cleanup() override;
			~SimpleImagePutTest() override = default;

		private:
			void* _image = nullptr;
	};
}

#endif

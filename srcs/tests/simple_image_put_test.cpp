/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_image_put_test.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbz_8 </var/spool/mail/kbz_8>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 20:57:22 by kbz_8             #+#    #+#             */
/*   Updated: 2023/12/24 16:45:20 by kbz_8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tests/simple_image_put_test.h>

namespace mlxut
{
	void SimpleImagePutTest::setup()
	{
		_image = mlx_png_file_to_image(_mlx, "resources/assets/logo.png", nullptr, nullptr);
	}

	void SimpleImagePutTest::run()
	{
		mlx_put_image_to_window(_mlx, _win, _image, 20, 20);
	}

	void SimpleImagePutTest::cleanup()
	{
		mlx_destroy_image(_mlx, _image);
	}
}

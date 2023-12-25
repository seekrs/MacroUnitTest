/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_image_put_test.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbz_8 </var/spool/mail/kbz_8>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 20:57:22 by kbz_8             #+#    #+#             */
/*   Updated: 2023/12/25 15:45:47 by kbz_8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tests/multiple_image_put_test.h>

namespace mlxut
{
	void MultipleImagePutTest::setup()
	{
		_image = mlx_png_file_to_image(_mlx, "resources/assets/logo.png", &_w, &_h);
	}

	void MultipleImagePutTest::run()
	{
		mlx_put_image_to_window(_mlx, _win, _image, 0, 0);
		mlx_put_image_to_window(_mlx, _win, _image, _w, 0);
		mlx_put_image_to_window(_mlx, _win, _image, 0, _h);
		mlx_put_image_to_window(_mlx, _win, _image, _w, _h);
	}

	void MultipleImagePutTest::cleanup()
	{
		mlx_destroy_image(_mlx, _image);
	}
}

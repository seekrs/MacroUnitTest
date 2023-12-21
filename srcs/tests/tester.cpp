/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 21:38:52 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/22 00:21:39 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tests/tester.h>
#include <tests/simple_pixel_put_test.h>

namespace mlxut
{
	void Tester::runAllTests()
	{
		_mlx = mlx_init();
		_win = mlx_new_window(_mlx, MLX_WIN_WIDTH, MLX_WIN_HEIGHT, "tester");
		_tests.emplace_back(std::make_unique<SimplePixelPutTest>(_mlx, _win));
		for(auto it = _tests.begin(); it != _tests.end(); ++it)
		{
			(*it)->setup();

			mlx_loop_hook(_mlx, [](void* data) -> int
			{
				BaseTest* test = static_cast<BaseTest*>(data);
				mlx_clear_window(test->_mlx, test->_win);
				test->run();
				// TODO : retrieve graphics data
				static int i = 0;
				if(i++ > 2000)
				{
					mlx_loop_end(test->_mlx);
					i = 0;
				}
				return 0;
			}, it->get());

			mlx_loop(_mlx);
			(*it)->cleanup();
		}
		_tests.clear();
		mlx_destroy_window(_mlx, _win);
		mlx_destroy_display(_mlx);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 21:38:52 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/23 01:49:29 by kbz_8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <renderer.h>
#include <tests/tester.h>
#include <components/render_results.h>
#include <tests/simple_pixel_put_test.h>

namespace mlxut
{
	void Tester::runAllTests(const Renderer& renderer, RenderResults& render_results)
	{
		_mlx = mlx_init();
		_tests.emplace_back(std::make_unique<SimplePixelPutTest>(_mlx));
		for(auto it = _tests.begin(); it != _tests.end(); ++it)
		{
			void* render_target = mlx_new_image(_mlx, MLX_WIN_WIDTH, MLX_WIN_HEIGHT);
			void* win = mlx_new_window(_mlx, MLX_WIN_WIDTH, MLX_WIN_HEIGHT, static_cast<const char*>(render_target));
			void* test = mlx_png_file_to_image(_mlx, "resources/assets/logo.png", nullptr, nullptr);
			mlx_put_image_to_window(_mlx, win, test, 10, 10);
			void* win2 = mlx_new_window(_mlx, MLX_WIN_WIDTH, MLX_WIN_HEIGHT, "caca"); 
			mlx_put_image_to_window(_mlx, win2, render_target, 0, 0);
			(*it)->setRenderData(win, render_target);

			(*it)->setup();

			mlx_loop_hook(_mlx, [](void* data) -> int
			{
				BaseTest* test = static_cast<BaseTest*>(data);
				//mlx_clear_window(test->_mlx, test->_win);
				test->run();
				static int i = 0;
				std::cout << i << std::endl;
				if(++i > 2000)
					mlx_loop_end(test->_mlx);
				return 0;
			}, it->get());

			mlx_loop(_mlx);
			(*it)->cleanup();

			mlx_destroy_window(_mlx, win);
			mlx_destroy_window(_mlx, win2);

			// maybe find a better way to retrive texture data :/
			std::vector<uint32_t> pixels;
			for(int y = 0; y < MLX_WIN_HEIGHT; y++)
			{
				for(int x = 0; x < MLX_WIN_WIDTH; x++)
				{
					pixels.push_back(mlx_get_image_pixel(_mlx, render_target, x, y));
//					std::cout << std::hex << pixels.back() << " ";
				}
//				std::cout << std::endl;
			}
			SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pixels.data(), MLX_WIN_WIDTH, MLX_WIN_HEIGHT, 32, 4 * MLX_WIN_WIDTH, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
			render_results.addResult(SDL_CreateTextureFromSurface(renderer.getNativeRenderer(), surface));
			SDL_FreeSurface(surface);
			mlx_destroy_image(_mlx, test);
			mlx_destroy_image(_mlx, render_target);
		}
		_tests.clear();
		mlx_destroy_display(_mlx);
	}
}

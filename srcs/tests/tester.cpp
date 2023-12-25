/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 21:38:52 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/25 15:46:19 by kbz_8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <renderer.h>
#include <tests/tester.h>
#include <components/render_results.h>
#include <tests/simple_pixel_put_test.h>
#include <tests/simple_image_put_test.h>
#include <tests/simple_text_put_test.h>
#include <tests/multiple_image_put_test.h>

namespace mlxut
{
	void Tester::createAllTests(const Renderer& renderer)
	{
		_tests.emplace_back(std::make_shared<SimplePixelPutTest>(renderer));
		_tests.emplace_back(std::make_shared<SimpleImagePutTest>(renderer));
		_tests.emplace_back(std::make_shared<SimpleTextPutTest>(renderer));
		_tests.emplace_back(std::make_shared<MultipleImagePutTest>(renderer));
	}

	void Tester::runAllTests(const Renderer& renderer)
	{
		for(auto& test : _tests)
		{
			test->destroyResult();

			void* mlx = mlx_init();
			void* render_target = mlx_new_image(mlx, MLX_WIN_WIDTH, MLX_WIN_HEIGHT);
			void* win = mlx_new_window(mlx, MLX_WIN_WIDTH, MLX_WIN_HEIGHT, static_cast<const char*>(render_target));
			test->setRenderData(mlx, win);

			test->setup();

			mlx_loop_hook(mlx, [](void* data) -> int
			{
				BaseTest* test = static_cast<BaseTest*>(data);
				mlx_clear_window(test->_mlx, test->_win);
				test->run();
				mlx_loop_end(test->_mlx);
				return 0;
			}, test.get());

			mlx_loop(mlx);
			test->cleanup();

			mlx_destroy_window(mlx, win);

			// maybe find a better way to retrive texture data :/
			std::vector<uint32_t> pixels;
			for(int y = 0; y < MLX_WIN_HEIGHT; y++)
			{
				for(int x = 0; x < MLX_WIN_WIDTH; x++)
					pixels.push_back(mlx_get_image_pixel(mlx, render_target, x, y));
			}
			SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pixels.data(), MLX_WIN_WIDTH, MLX_WIN_HEIGHT, 32, 4 * MLX_WIN_WIDTH, rmask, gmask, bmask, amask);
			test->setResultTexture(SDL_CreateTextureFromSurface(renderer.getNativeRenderer(), surface));
			std::filesystem::path respath = "resources/assets/tests_references";
			respath /= test->getName() + ".png";
			IMG_SavePNG(surface, respath.string().c_str());
			SDL_FreeSurface(surface);
			mlx_destroy_image(mlx, render_target);
			mlx_destroy_display(mlx);
		}
	}
}

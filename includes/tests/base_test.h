/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_test.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:15:26 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/24 17:24:27 by kbz_8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_BASE_TEST__
#define __MLX_UT_BASE_TEST__

#include <pch.h>
#include <loader/loader.h>

namespace mlxut
{
	class BaseTest
	{
		friend class Tester;

		public:
			BaseTest(const std::string& name) : _name(name)
			{

				//_reference = IMG_LoadTexture(renderer.getNativeRenderer(), "./resources/assets/logo.png");
			}
			inline void setRenderData(void* mlx, void* win) noexcept { _mlx = mlx; _win = win; }
			inline const std::string& getName() const noexcept { return _name; }
			virtual void setup() {};
			virtual void run() = 0;
			virtual void cleanup() {};
			virtual ~BaseTest() = default;

		protected:
			std::string _name;
			void* _mlx = nullptr;
			void* _win = nullptr;
			SDL_Texture* _reference = nullptr;
	};
}

#endif

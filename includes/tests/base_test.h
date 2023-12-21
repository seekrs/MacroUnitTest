/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_test.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:15:26 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/21 22:00:24 by maldavid         ###   ########.fr       */
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
			BaseTest(void* mlx, void* win) : _mlx(mlx), _win(win) {}
			virtual void setup() {};
			virtual void run() = 0;
			virtual void cleanup() {};
			virtual ~BaseTest() = default;

		protected:
			void* _mlx = nullptr;
			void* _win = nullptr;
			SDL_Texture* _result = nullptr;
	};
}

#endif

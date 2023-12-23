/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_test.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:15:26 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/22 22:48:08 by kbz_8            ###   ########.fr       */
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
			BaseTest(void* mlx) : _mlx(mlx) {}
			inline void setRenderData(void* win, void* render_target) noexcept { _win = win; _render_target = render_target; }
			virtual void setup() {};
			virtual void run() = 0;
			virtual void cleanup() {};
			virtual ~BaseTest() = default;

		protected:
			void* _mlx = nullptr;
			void* _win = nullptr;
			void* _render_target = nullptr;
	};
}

#endif

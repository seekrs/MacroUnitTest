/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 21:35:21 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/22 22:46:36 by kbz_8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_TESTER__
#define __MLX_UT_TESTER__

#include <pch.h>
#include <tests/base_test.h>

namespace mlxut
{
	constexpr const int MLX_WIN_WIDTH = 400;
	constexpr const int MLX_WIN_HEIGHT = 400;

	class Tester
	{
		public:
			Tester() = default;
			void runAllTests(const class Renderer& renderer, class RenderResults& render_results);
			~Tester() = default;

		private:
			std::vector<std::unique_ptr<BaseTest>> _tests;
			void* _mlx = nullptr;
	};
}

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 21:35:21 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/21 22:29:28 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_TESTER__
#define __MLX_UT_TESTER__

#include <pch.h>
#include <tests/base_test.h>

namespace mlxut
{
	constexpr const int MLX_WIN_WIDTH = 100;
	constexpr const int MLX_WIN_HEIGHT = 100;

	class Tester
	{
		public:
			Tester() = default;
			void runAllTests();
			~Tester() = default;

		private:
			std::vector<std::unique_ptr<BaseTest>> _tests;
			void* _mlx = nullptr;
			void* _win = nullptr;
	};
}

#endif

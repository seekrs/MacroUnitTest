/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 21:35:21 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/24 16:44:15 by kbz_8            ###   ########.fr       */
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
			void createAllTests();
			void runAllTests(const class Renderer& renderer, class RenderResults& render_results);
			inline const std::vector<std::shared_ptr<BaseTest>>& getAllTests() const { return _tests; }
			inline std::size_t getActiveTestIndex() const noexcept { return _active_test; }
			inline void changeActiveTest(std::size_t index) noexcept
			{
				if(index >= _tests.size())
					return;
				_active_test = index;
			}
			~Tester() = default;

		private:
			std::vector<std::shared_ptr<BaseTest>> _tests;
			std::size_t _active_test = 0;
	};
}

#endif

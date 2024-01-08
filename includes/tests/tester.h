/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 21:35:21 by maldavid          #+#    #+#             */
/*   Updated: 2024/01/08 00:44:22 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_TESTER__
#define __MLX_UT_TESTER__

#include <pch.h>
#include <tests/base_test.h>
#include <lua_loader.h>

namespace mlxut
{
	class Tester
	{
		public:
			Tester() = default;
			void createAllTests(const Renderer& renderer);
			void runAllTests();
			inline const std::vector<std::shared_ptr<Test>>& getAllTests() const { return _tests; }
			inline bool testsAreRunning() const noexcept { return _is_running; }
			inline std::size_t getActiveTestIndex() const noexcept { return _active_test; }
			inline std::size_t getTestsPassedNumber() const noexcept { return _tests_passed; }
			inline std::size_t getTestsFailedNumber() const noexcept { return _tests_failed; }
			inline std::size_t getTestsPendingNumber() const noexcept { return _tests_pending; }
			inline void changeActiveTest(std::size_t index) noexcept
			{
				if(index >= _tests.size())
					return;
				_active_test = index;
			}
			~Tester() = default;

		private:
			double compareImages(const std::vector<uint32_t>& test_res, const std::vector<uint32_t>& ref);
			void testRunner(struct SharedMemoryData* data);

		private:
			LuaLoader _loader;
			std::vector<std::shared_ptr<Test>> _tests;
			std::size_t _active_test = 0;
			std::size_t _tests_passed = 0;
			std::size_t _tests_failed = 0;
			std::size_t _tests_pending = 0;
			bool _is_running = false;
	};
}

#endif

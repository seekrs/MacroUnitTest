/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:50:47 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/23 20:48:26 by kbz_8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_TESTS_LIST__
#define __MLX_UT_TESTS_LIST__

#include <pch.h>
#include <components/panel.h>

namespace mlxut
{
	class TestList : public Panel
	{
		public:
			TestList(class Tester* tester);
			void onUpdate(ivec2 size) override;
			~TestList() override = default;

		private:
			class Tester* _tester = nullptr;
	};
}

#endif

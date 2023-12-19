/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stats.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:41:31 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/19 19:42:08 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_TEST_STATS__
#define __MLX_UT_TEST_STATS__

#include <pch.h>
#include <components/panel.h>

namespace mlxut
{
	class TestStats : public Panel
	{
		public:
			TestStats();
			void onUpdate(ivec2 size) override;
			~TestStats() override = default;
	};
}

#endif

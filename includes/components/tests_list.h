/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:50:47 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/19 19:13:56 by maldavid         ###   ########.fr       */
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
			TestList();
			void onUpdate(ivec2 size) override;
			~TestList() override = default;
	};
}

#endif

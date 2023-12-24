/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_text_put_test.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 21:26:54 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/24 17:04:38 by kbz_8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tests/simple_text_put_test.h>

namespace mlxut
{
	void SimpleTextPutTest::run()
	{
		mlx_string_put(_mlx, _win, 10, 10, 0xFF00FFFF, "this is a text");
	}
}

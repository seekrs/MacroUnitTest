/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_text_put_test.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbz_8 </var/spool/mail/kbz_8>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 20:56:31 by kbz_8             #+#    #+#             */
/*   Updated: 2023/12/24 17:03:11 by kbz_8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_SIMPLE_TEXT_PUT_TEST__
#define __MLX_UT_SIMPLE_TEXT_PUT_TEST__

#include <tests/base_test.h>

namespace mlxut
{
	class SimpleTextPutTest final : public BaseTest
	{
		public:
			SimpleTextPutTest() : BaseTest("Simple Text Put") {}
			void run() override;
			~SimpleTextPutTest() override = default;
	};
}

#endif

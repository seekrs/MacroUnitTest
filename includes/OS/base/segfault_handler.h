/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segfault_handler.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:35:25 by maldavid          #+#    #+#             */
/*   Updated: 2024/01/07 17:37:39 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_OS_BASE_SEGFAULT_HANDLER__
#define __MLX_UT_OS_BASE_SEGFAULT_HANDLER__

namespace mlxut::OS::base
{
	class SegFaultHandler
	{
		public:
			SegFaultHandler() = default;
			virtual ~SegFaultHandler() = default;
	};
}

#endif

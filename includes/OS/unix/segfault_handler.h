/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segfault_handler.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:37:59 by maldavid          #+#    #+#             */
/*   Updated: 2024/01/07 18:48:36 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_OS_UNIX_SEGFAULT_HANDLER__
#define __MLX_UT_OS_UNIX_SEGFAULT_HANDLER__

#include <OS/base/segfault_handler.h>
#include <pch.h>

namespace mlxut::OS::unix
{
	class SegFaultHandler : public base::SegFaultHandler
	{
		public:
			SegFaultHandler()
			{
				signal(SIGSEGV, &SegFaultHandler::signalHandler);
			}
			~SegFaultHandler() = default;

		private:
			static inline void signalHandler(int signum)
			{
				if(signum != SIGSEGV)
					return;
				std::cerr << "Unix segfault handler catched a segmentation fault... exit" << std::endl;
				std::terminate();
			}
	};
}

#endif

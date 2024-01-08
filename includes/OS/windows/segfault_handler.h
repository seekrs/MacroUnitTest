/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segfault_handler.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:44:41 by maldavid          #+#    #+#             */
/*   Updated: 2024/01/07 18:38:23 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_OS_WINDOWS_SEGFAULT_HANDLER__
#define __MLX_UT_OS_WINDOWS_SEGFAULT_HANDLER__

#include <OS/base/segfault_handler.h>
#include <pch.h>

namespace mlxut::OS::windows
{
	class SegFaultHandler : public base::SegFaultHandler
	{
		public:
			SegFaultHandler()
			{
				SetUnhandledExceptionFilter(&SegFaultHandler::TopLevelExceptionHandler);
			}
			~SegFaultHandler() = default;

		private:
			static inline LONG WINAPI TopLevelExceptionHandler(PEXCEPTION_POINTERS pExceptionInfo)
			{
				std::cerr << "Windows segfault handler catched a segmentation fault... exit" << std::endl;
				std::exit(-1);
				return EXCEPTION_CONTINUE_SEARCH;
			}
	};
}

#endif

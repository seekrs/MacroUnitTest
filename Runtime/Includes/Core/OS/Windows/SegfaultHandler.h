#ifndef MLX_UT_OS_WINDOWS_SEGFAULT_HANDLER
#define MLX_UT_OS_WINDOWS_SEGFAULT_HANDLER

#include <Pch.h>
#include <Core/OS/Base/SegfaultHandler.h>

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

#ifndef MLX_UT_OS_UNIX_SEGFAULT_HANDLER
#define MLX_UT_OS_UNIX_SEGFAULT_HANDLER

#include <Pch.h>
#include <Core/OS/Base/SegfaultHandler.h>

namespace mlxut::OS::unix
{
	class SegFaultHandler : public base::SegFaultHandler
	{
		public:
			SegFaultHandler()
			{
				signal(SIGSEGV, &SegFaultHandler::SignalHandler);
			}
			~SegFaultHandler() = default;

		private:
			static inline void SignalHandler(int signum)
			{
				if(signum != SIGSEGV)
					return;
				std::cerr << "Unix segfault handler catched a segmentation fault... exit" << std::endl;
				std::terminate();
			}
	};
}

#endif

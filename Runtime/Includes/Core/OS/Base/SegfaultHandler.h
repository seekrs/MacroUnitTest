#ifndef MLX_UT_OS_BASE_SEGFAULT_HANDLER
#define MLX_UT_OS_BASE_SEGFAULT_HANDLER

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

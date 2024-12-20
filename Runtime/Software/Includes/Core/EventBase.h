#ifndef MLX_UT_CORE_BASE_EVENT
#define MLX_UT_CORE_BASE_EVENT

#include <Core/Enums.h>

namespace mlxut
{
	struct EventBase
	{
		virtual Event What() const = 0;
	};
}

#endif

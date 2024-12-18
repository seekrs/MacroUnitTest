#ifndef MLX_UT_LOADER
#define MLX_UT_LOADER

#include <Pch.h>
#include <Core/Loader/PFN.h>

namespace mlxut
{
	bool LoadMLX(const std::filesystem& path) noexcept;
	void UnloadMLX() noexcept;
}

#define MLX_UT_MLX_FUNCTION(fn) extern PFN_##fn fn;
	#include <Core/Loader/Prototypes.h>
#undef MLX_UT_MLX_FUNCTION

#endif

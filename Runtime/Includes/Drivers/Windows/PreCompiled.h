#ifndef MLX_UT_DRIVERS_WINDOWS_PRE_COMPILED_HEADER
#define MLX_UT_DRIVERS_WINDOWS_PRE_COMPILED_HEADER

#include <Core/CompilationProfile.h>

#include <cstdlib>

#ifdef MLX_UT_PLAT_WINDOWS
	#ifndef NOMINMAX
		#define NOMINMAX // For windows.h
	#endif
	#include <windows.h>
	#include <shellapi.h>
	#include <dwmapi.h>
	#include <winuser.h>
#endif

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:36:30 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/20 19:27:52 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <loader/loader.h>
#include <errors.h>

#ifdef _WIN32
	typedef const char* LPCSTR;
	typedef struct HINSTANCE__* HINSTANCE;
	typedef HINSTANCE HMODULE;
	#if defined(_MINWINDEF_)
		/* minwindef.h defines FARPROC, and attempting to redefine it may conflict with -Wstrict-prototypes */
	#elif defined(_WIN64)
		typedef __int64 (__stdcall* FARPROC)(void);
	#else
		typedef int (__stdcall* FARPROC)(void);
	#endif
	__declspec(dllimport) HMODULE __stdcall LoadLibraryA(LPCSTR);
	__declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE, LPCSTR);
	__declspec(dllimport) int __stdcall FreeLibrary(HMODULE);
	#define FARTPROC FARPROC // lol farts
#else
	#include <dlfcn.h>
#endif

namespace mlxut
{
	void* __module = nullptr;

	void loadSymbols(void* module, void* (*load)(void*, const char*)) noexcept;

	bool loadMLX() noexcept
	{
		#if defined(_WIN32)
			HMODULE module = LoadLibraryA("libmlx.dll");
			if(!module)
			{
				core::error::report(e_kind::error, "cannot open libmlx.dll");
				return false;
			}

			loadSymbols(module, GetProcAddress);
		#elif defined(__APPLE__)
			void* module = dlopen("./libmlx.dylib", RTLD_NOW | RTLD_LOCAL);
			if(!module)
			{
				core::error::report(e_kind::error, "cannot open libmlx.dylib");
				return false;
			}

			loadSymbols(module, dlsym);
		#else
			void* module = dlopen("./libmlx.so", RTLD_NOW | RTLD_LOCAL);
			if(!module)
			{
				core::error::report(e_kind::error, "cannot open libmlx.so");
				return false;
			}

			loadSymbols(module, dlsym);
		#endif
		__module = module;
		return true;
	}

	void unloadMLX() noexcept
	{
		#if defined(_WIN32)
			FreeLibrary((HMODULE)__module);
		#else
			dlclose(__module);
		#endif
		__module = nullptr;
	}

	void loadSymbols(void* module, void* (*load)(void*, const char*)) noexcept
	{

	}
}

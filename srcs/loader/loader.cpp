/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:36:30 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/20 23:52:12 by maldavid         ###   ########.fr       */
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

PFN_mlx_init mlx_init;
PFN_mlx_new_window mlx_new_window;
PFN_mlx_loop_hook mlx_loop_hook;
PFN_mlx_loop mlx_loop;
PFN_mlx_loop_end mlx_loop_end;
PFN_mlx_mouse_show mlx_mouse_show;
PFN_mlx_mouse_hide mlx_mouse_hide;
PFN_mlx_mouse_move mlx_mouse_move;
PFN_mlx_mouse_get_pos mlx_mouse_get_pos;
PFN_mlx_on_event mlx_on_event;
PFN_mlx_pixel_put mlx_pixel_put;
PFN_mlx_new_image mlx_new_image;
PFN_mlx_get_image_pixel mlx_get_image_pixel;
PFN_mlx_set_image_pixel mlx_set_image_pixel;
PFN_mlx_put_image_to_window mlx_put_image_to_window;
PFN_mlx_destroy_image mlx_destroy_image;
PFN_mlx_png_file_to_image mlx_png_file_to_image;
PFN_mlx_jpg_file_to_image mlx_jpg_file_to_image;
PFN_mlx_bmp_file_to_image mlx_bmp_file_to_image;
PFN_mlx_string_put mlx_string_put;
PFN_mlx_set_font mlx_set_font;
PFN_mlx_set_font_scale mlx_set_font_scale;
PFN_mlx_clear_window mlx_clear_window;
PFN_mlx_destroy_window mlx_destroy_window;
PFN_mlx_destroy_display mlx_destroy_display;
PFN_mlx_get_screens_size mlx_get_screens_size;

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
				core::error::report(e_kind::error, "cannot load libmlx.dll");
				return false;
			}

			loadSymbols(module, GetProcAddress);
		#elif defined(__APPLE__)
			void* module = dlopen("./libmlx.dylib", RTLD_LAZY | RTLD_LOCAL);
			if(!module)
			{
				core::error::report(e_kind::error, "cannot load libmlx.dylib");
				return false;
			}

			loadSymbols(module, dlsym);
		#else
			void* module = dlopen("./libmlx.so", RTLD_NOW | RTLD_LOCAL);
			if(!module)
			{
				core::error::report(e_kind::error, "cannot load libmlx.so");
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
		*(void**)(&mlx_init) = load(module, "mlx_init");
		*(void**)(&mlx_new_window) = load(module, "mlx_new_image");
		*(void**)(&mlx_loop_hook) = load(module, "mlx_loop_hook");
		*(void**)(&mlx_loop) = load(module, "mlx_loop");
		*(void**)(&mlx_loop_end) = load(module, "mlx_loop_end");
		*(void**)(&mlx_mouse_show) = load(module, "mlx_mouse_show");
		*(void**)(&mlx_mouse_hide) = load(module, "mlx_mouse_hide");
		*(void**)(&mlx_mouse_move) = load(module, "mlx_mouse_move");
		*(void**)(&mlx_mouse_get_pos) = load(module, "mlx_mouse_get_pos");
		*(void**)(&mlx_on_event) = load(module, "mlx_on_event");
		*(void**)(&mlx_pixel_put) = load(module, "mlx_pixel_put");
		*(void**)(&mlx_new_image) = load(module, "mlx_new_image");
		*(void**)(&mlx_get_image_pixel) = load(module, "mlx_get_image_pixel");
		*(void**)(&mlx_set_image_pixel) = load(module, "mlx_set_image_pixel");
		*(void**)(&mlx_put_image_to_window) = load(module, "mlx_put_image_to_window");
		*(void**)(&mlx_destroy_image) = load(module, "mlx_destroy_image");
		*(void**)(&mlx_png_file_to_image) = load(module, "mlx_png_file_to_image");
		*(void**)(&mlx_jpg_file_to_image) = load(module, "mlx_jpg_file_to_image");
		*(void**)(&mlx_bmp_file_to_image) = load(module, "mlx_bmp_file_to_image");
		*(void**)(&mlx_string_put) = load(module, "mlx_string_put");
		*(void**)(&mlx_set_font) = load(module, "mlx_set_font");
		*(void**)(&mlx_set_font_scale) = load(module, "mlx_set_font_scale");
		*(void**)(&mlx_clear_window) = load(module, "mlx_clear_window");
		*(void**)(&mlx_destroy_window) = load(module, "mlx_destroy_window");
		*(void**)(&mlx_destroy_display) = load(module, "mlx_destroy_display");
		*(void**)(&mlx_get_screens_size) = load(module, "mlx_get_screens_size");
	}
}

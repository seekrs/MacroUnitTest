/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfn.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 20:39:06 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/20 22:24:27 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_PFN__
#define __MLX_UT_PFN__

typedef enum
{
	MLX_KEYDOWN = 0,
	MLX_KEYUP = 1,
	MLX_MOUSEDOWN = 2,
	MLX_MOUSEUP = 3,
	MLX_MOUSEWHEEL = 4,
	MLX_WINDOW_EVENT = 5
} mlx_event_type;

typedef void* (*PFN_mlx_init)();
typedef void* (*PFN_mlx_new_window)(void*, int, int, const char*);
typedef int (*PFN_mlx_loop_hook)(void*, int (*)(void*), void*);
typedef int (*PFN_mlx_loop)(void*);
typedef int (*PFN_mlx_loop_end)(void*);
typedef int (*PFN_mlx_mouse_show)();
typedef int (*PFN_mlx_mouse_hide)();
typedef int (*PFN_mlx_mouse_move)(void*, void*, int, int);
typedef int (*PFN_mlx_mouse_get_pos)(void*, int*, int*);
typedef int (*PFN_mlx_on_event)(void*, void*, mlx_event_type, int (*)(int, void*), void*);
typedef int (*PFN_mlx_pixel_put)(void*, void*, int, int, int);
typedef void* (*PFN_mlx_new_image)(void*, int, int);
typedef int (*PFN_mlx_get_image_pixel)(void*, void*, int, int);
typedef void (*PFN_mlx_set_image_pixel)(void*, void*, int, int, int);
typedef int (*PFN_mlx_put_image_to_window)(void*, void*, void*, int, int);
typedef int (*PFN_mlx_destroy_image)(void*, void*);
typedef void* (*PFN_mlx_png_file_to_image)(void*, char*, int*, int*);
typedef void* (*PFN_mlx_jpg_file_to_image)(void*, char*, int*, int*);
typedef void* (*PFN_mlx_bmp_file_to_image)(void*, char*, int*, int*);
typedef int (*PFN_mlx_string_put)(void*, void*, int, int, int, char*);
typedef void (*PFN_mlx_set_font)(void*, void*, char*);
typedef void (*PFN_mlx_set_font_scale)(void*, void*, char*, float);
typedef int (*PFN_mlx_clear_window)(void*, void*);
typedef int (*PFN_mlx_destroy_window)(void*, void*);
typedef int (*PFN_mlx_destroy_display)(void*);
typedef int (*PFN_mlx_get_screens_size)(void*, int*, int*);

#endif

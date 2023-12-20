/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:35:42 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/20 21:15:57 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_LOADER__
#define __MLX_UT_LOADER__

#include <pch.h>
#include <loader/pfn.h>

namespace mlxut
{
	bool loadMLX() noexcept;
	void unloadMLX() noexcept;

	extern PFN_mlx_init mlx_init;
	extern PFN_mlx_new_window mlx_new_window;
	extern PFN_mlx_loop_hook mlx_loop_hook;
	extern PFN_mlx_loop mlx_loop;
	extern PFN_mlx_loop_end mlx_loop_end;
	extern PFN_mlx_mouse_show mlx_mouse_show;
	extern PFN_mlx_mouse_hide mlx_mouse_hide;
	extern PFN_mlx_mouse_move mlx_mouse_move;
	extern PFN_mlx_mouse_get_pos mlx_mouse_get_pos;
	extern PFN_mlx_on_event mlx_on_event;
	extern PFN_mlx_pixel_put mlx_pixel_put;
	extern PFN_mlx_new_image mlx_new_image;
	extern PFN_mlx_get_image_pixel mlx_get_image_pixel;
	extern PFN_mlx_set_image_pixel mlx_set_image_pixel;
	extern PFN_mlx_put_image_to_window mlx_put_image_to_window;
	extern PFN_mlx_destroy_image mlx_destroy_image;
	extern PFN_mlx_png_file_to_image mlx_png_file_to_image;
	extern PFN_mlx_jpg_file_to_image mlx_jpg_file_to_image;
	extern PFN_mlx_bmp_file_to_image mlx_bmp_file_to_image;
	extern PFN_mlx_string_put mlx_string_put;
	extern PFN_mlx_set_font mlx_set_font;
	extern PFN_mlx_set_font_scale mlx_set_font_scale;
	extern PFN_mlx_clear_window mlx_clear_window;
	extern PFN_mlx_destroy_window mlx_destroy_window;
	extern PFN_mlx_destroy_display mlx_destroy_display;
	extern PFN_mlx_get_screens_size mlx_get_screens_size;
}

#endif

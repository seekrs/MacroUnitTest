#ifndef MLX_UT_PFN
#define MLX_UT_PFN

#include <Pch.h>

#define MLX_DEFINE_HANDLE(object) typedef struct object##_handler* object

typedef enum mlx_event_type
{
	MLX_KEYDOWN = 0,
	MLX_KEYUP = 1,
	MLX_MOUSEDOWN = 2,
	MLX_MOUSEUP = 3,
	MLX_MOUSEWHEEL = 4,
	MLX_WINDOW_EVENT = 5
} mlx_event_type;

MLX_DEFINE_HANDLE(mlx_context);
MLX_DEFINE_HANDLE(mlx_window);
MLX_DEFINE_HANDLE(mlx_image);

typedef union mlx_color
{
	struct
	{
		// Assuming little endian
		std::uint8_t a;
		std::uint8_t b;
		std::uint8_t g;
		std::uint8_t r;
	};
	std::uint32_t rgba;
} mlx_color;

typedef struct mlx_window_create_info
{
	const char* title;
	int width;
	int height;
	bool is_fullscreen;
	bool is_resizable;
} mlx_window_create_info;

mlx_context (*PFN_mlx_init)();
void        (*PFN_mlx_set_fps_goal)(mlx_context, int);
void        (*PFN_mlx_destroy_context)(mlx_context);
mlx_window  (*PFN_mlx_new_window)(mlx_context, const mlx_window_create_info*);
void        (*PFN_mlx_destroy_window)(mlx_context, mlx_window);
void        (*PFN_mlx_set_window_position)(mlx_context, mlx_window, int, int);
void        (*PFN_mlx_set_window_size)(mlx_context, mlx_window, int, int);
void        (*PFN_mlx_set_window_title)(mlx_context, mlx_window, const char*);
void        (*PFN_mlx_set_window_fullscreen)(mlx_context, mlx_window, bool);
void        (*PFN_mlx_get_window_position)(mlx_context, mlx_window, int*, int*);
void        (*PFN_mlx_get_window_size)(mlx_context, mlx_window, int*, int*);
void        (*PFN_mlx_clear_window)(mlx_context, mlx_window, mlx_color);
void        (*PFN_mlx_get_screen_size)(mlx_context, mlx_window, int*, int*);
void        (*PFN_mlx_add_loop_hook)(mlx_context, void(*f)(void*), void*);
void        (*PFN_mlx_loop)(mlx_context);
void        (*PFN_mlx_loop_end)(mlx_context);
void        (*PFN_mlx_mouse_show)(mlx_context);
void        (*PFN_mlx_mouse_hide)(mlx_context);
void        (*PFN_mlx_mouse_move)(mlx_context, mlx_window, int, int);
void        (*PFN_mlx_mouse_get_pos)(mlx_context, int*, int*);
void        (*PFN_mlx_on_event)(mlx_context, mlx_window, mlx_event_type, void(*)(int, void*), void*);
void        (*PFN_mlx_pixel_put)(mlx_context, mlx_window, int, int, mlx_color);
mlx_image   (*PFN_mlx_new_image)(mlx_context, int, int);
mlx_image   (*PFN_mlx_new_image_from_file)(mlx_context, char*, int*, int*);
void        (*PFN_mlx_destroy_image)(mlx_context, mlx_image);
mlx_color   (*PFN_mlx_get_image_pixel)(mlx_context, mlx_image, int, int);
void        (*PFN_mlx_set_image_pixel)(mlx_context, mlx_image, int, int, mlx_color);
void        (*PFN_mlx_put_image_to_window)(mlx_context, mlx_window, mlx_image, int, int);
void        (*PFN_mlx_string_put)(mlx_context, mlx_window, int, int, mlx_color, char*);
void        (*PFN_mlx_set_font)(mlx_context, char*);
void        (*PFN_mlx_set_font_scale)(mlx_context, char*, float);

void        (*PFN_mlx_set_window_max_size)(mlx_context, mlx_window, int, int);
void        (*PFN_mlx_set_window_min_size)(mlx_context, mlx_window, int, int);
void        (*PFN_mlx_maximise_window)(mlx_context, mlx_window);
void        (*PFN_mlx_minimize_window)(mlx_context, mlx_window);
void        (*PFN_mlx_restore_window)(mlx_context, mlx_window);
void        (*PFN_mlx_pixel_put_array)(mlx_context, mlx_window, int, int, mlx_color*, std::size_t);
void        (*PFN_mlx_pixel_put_region)(mlx_context, mlx_window, int, int, int, int, mlx_color*);
void        (*PFN_mlx_get_image_region)(mlx_context, mlx_image, int, int, int, int, mlx_color*);
void        (*PFN_mlx_set_image_region)(mlx_context, mlx_image, int, int, int, int, mlx_color*);
void        (*PFN_mlx_put_transformed_image_to_window)(mlx_context, mlx_window, mlx_image, int, int, float, float, float);

#endif

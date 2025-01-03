#ifdef MLX_UT_MLX_FUNCTION
	#ifndef MLX_UT_ONLY_TESTS_FUNCTIONS
		MLX_UT_MLX_FUNCTION(mlx_init)
		MLX_UT_MLX_FUNCTION(mlx_destroy_context)
		MLX_UT_MLX_FUNCTION(mlx_new_window)
		MLX_UT_MLX_FUNCTION(mlx_destroy_window)
		MLX_UT_MLX_FUNCTION(mlx_add_loop_hook)
		MLX_UT_MLX_FUNCTION(mlx_loop)
		MLX_UT_MLX_FUNCTION(mlx_loop_end)
		MLX_UT_MLX_FUNCTION(mlx_set_fps_goal)
		MLX_UT_MLX_FUNCTION(mlx_set_window_position)
		MLX_UT_MLX_FUNCTION(mlx_set_window_size)
		MLX_UT_MLX_FUNCTION(mlx_set_window_title)
		MLX_UT_MLX_FUNCTION(mlx_set_window_fullscreen)
		MLX_UT_MLX_FUNCTION(mlx_get_window_position)
		MLX_UT_MLX_FUNCTION(mlx_get_screen_size)
		MLX_UT_MLX_FUNCTION(mlx_mouse_show)
		MLX_UT_MLX_FUNCTION(mlx_mouse_hide)
		MLX_UT_MLX_FUNCTION(mlx_mouse_move)
		MLX_UT_MLX_FUNCTION(mlx_on_event)
		MLX_UT_MLX_FUNCTION(mlx_mouse_get_pos)

		MLX_UT_MLX_FUNCTION(mlx_set_window_max_size)
		MLX_UT_MLX_FUNCTION(mlx_set_window_min_size)
		MLX_UT_MLX_FUNCTION(mlx_maximise_window)
		MLX_UT_MLX_FUNCTION(mlx_minimize_window)
		MLX_UT_MLX_FUNCTION(mlx_restore_window)
	#endif

	#ifndef MLX_UT_ONLY_DIRECTLY_BINDABLE_FUNCTIONS
		MLX_UT_MLX_FUNCTION(mlx_get_window_size)
		MLX_UT_MLX_FUNCTION(mlx_new_image_from_file)
		MLX_UT_MLX_FUNCTION(mlx_string_put)
		MLX_UT_MLX_FUNCTION(mlx_set_font)
		MLX_UT_MLX_FUNCTION(mlx_set_font_scale)

		MLX_UT_MLX_FUNCTION(mlx_pixel_put_array)
		MLX_UT_MLX_FUNCTION(mlx_pixel_put_region)
		MLX_UT_MLX_FUNCTION(mlx_get_image_region)
		MLX_UT_MLX_FUNCTION(mlx_set_image_region)
	#endif

	MLX_UT_MLX_FUNCTION(mlx_clear_window)
	MLX_UT_MLX_FUNCTION(mlx_destroy_image)
	MLX_UT_MLX_FUNCTION(mlx_new_image)
	MLX_UT_MLX_FUNCTION(mlx_pixel_put)
	MLX_UT_MLX_FUNCTION(mlx_get_image_pixel)
	MLX_UT_MLX_FUNCTION(mlx_set_image_pixel)
	MLX_UT_MLX_FUNCTION(mlx_put_image_to_window)
	MLX_UT_MLX_FUNCTION(mlx_put_transformed_image_to_window)
#endif

function Test(mlx, win)
	mlx_set_font(mlx, mlx_utils.get_current_working_directory() .. "Resources/Fonts/OpenSans/OpenSans_Regular.ttf")
	mlx_string_put(mlx, win, 50, 50, mlx_color:new(0xFFFF00FF), "this is a string")
end

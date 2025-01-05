function Test(mlx, win)
	local color = mlx_color:new()

	mlx_set_font_scale(mlx, "Resources/Fonts/OpenSans/OpenSans_Regular.ttf", 36.0)
	color.rgba = 0xFFFF00FF
	mlx_string_put(mlx, win, 10, 20, color, "this is a string")
	mlx_set_font(mlx, "Resources/Fonts/OpenSans/OpenSans_Italic.ttf")
	color.rgba = 0xFF0000FF
	mlx_string_put(mlx, win, 50, 50, color, "macro unit tester")
	mlx_set_font_scale(mlx, "default", 32.0)
	color.rgba = 0x0000FFFF
	mlx_string_put(mlx, win, 150, 250, color, "yes")
	mlx_set_font_scale(mlx, "Resources/Fonts/OpenSans/OpenSans_ExtraBold.ttf", 45.0)
	color.rgba = 0xB4A8FFFFF
	mlx_string_put(mlx, win, 10, 350, color, "another string")
end

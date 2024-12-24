function Test(mlx, win)
	mlx_set_font_scale(mlx, "Resources/Fonts/OpenSans/OpenSans-Regular.ttf", 50.0)
	local color = mlx_color:new()
	color.rgba = 0xFFFF00FF
	mlx_string_put(mlx, win, 50, 50, color, "this is a string")
end

function Test(mlx, win)
	mlx_set_font(mlx, "Resources/Fonts/OpenSans/OpenSans-Regular.ttf")
	local color = mlx_color:new()
	color.rgba = 0xFFFF00FF
	mlx_string_put(mlx, win, 50, 50, color, "this is a string")
end

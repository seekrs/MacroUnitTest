function Test(mlx, win)
	local color = mlx_color:new()
	color.rgba = 0xFFFF00FF
	mlx_string_put(mlx, win, 10, 10, color, "this is a string")
	color.rgba = 0xFF0000FF
	mlx_string_put(mlx, win, 50, 50, color, "macro unit tester")
	color.rgba = 0x0000FFFF
	mlx_string_put(mlx, win, 150, 250, color, "yes")
	color.rgba = 0xB4A8FFFFF
	mlx_string_put(mlx, win, 10, 350, color, "another string")
end

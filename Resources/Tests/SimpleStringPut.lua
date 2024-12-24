function Test(mlx, win)
	local color = mlx_color:new()
	color.rgba = 0xFF0000FF
	mlx_string_put(mlx, win, 50, 50, color, "this is a string")
end

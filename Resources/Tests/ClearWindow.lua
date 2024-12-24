function Test(mlx, win)
	local color = mlx_color:new()
	color.rgba = 0xFF0000FF
	mlx_clear_window(mlx, win, color)
end

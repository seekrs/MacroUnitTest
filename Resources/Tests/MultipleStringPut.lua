function Test(mlx, win)
	mlx_string_put(mlx, win, 10, 10, mlx_color:new(0xFFFF00FF), "this is a string")
	mlx_string_put(mlx, win, 50, 50, mlx_color:new(0xFF0000FF), "macro unit tester")
	mlx_string_put(mlx, win, 150, 250, mlx_color:new(0x0000FFFF), "yes")
	mlx_string_put(mlx, win, 10, 350, mlx_color:new(0xB4A8FFFFF), "another string")
end

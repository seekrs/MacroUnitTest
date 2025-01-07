function Test(mlx, win)
	for y = 0, 40, 1 do
		for x = 0, 40, 1 do
			mlx_pixel_put(mlx, win, 180 + x, 180 + y, mlx_color:new(0xFF0000FF))
		end
	end
end

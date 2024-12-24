function Test(mlx, win)
	for y = 0, 40, 1 do
		for x = 0, 40, 1 do
			local color = mlx_color:new()
			color.rgba = 0xFF0000FF
			mlx_pixel_put(mlx, win, 180 + x, 180 + y, color)
		end
	end
end

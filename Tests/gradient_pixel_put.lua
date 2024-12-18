function TestOnUpdate(mlx, win)
	local color = 0
	for i = 0, 400, 1 do
		mlx_pixel_put(mlx, win, i, i, 0xFFFF0000 + color)
		mlx_pixel_put(mlx, win, 399 - i, i, 0xFF0000FF)
		if color < 255 then
			color = color + 1
		end
	end
end

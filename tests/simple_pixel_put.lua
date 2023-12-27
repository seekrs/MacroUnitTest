function TestOnUpdate(mlx, win)
	for y = 0, 40, 1 do
		for x = 0, 40, 1 do
			mlx_pixel_put(mlx, win, x, y, 0xFFFF0000);
		end
	end
end

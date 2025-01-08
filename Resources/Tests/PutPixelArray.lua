local pixels_data = {}

function Setup(mlx, win)
	local i = 1
	for i = 1, MLX_WIN_WIDTH * 200 do
		pixels_data[i] = mlx_color:new(0x0011FFFF);
	end
end

function Test(mlx, win)
	mlx_pixel_put_array(mlx, win, 50, 10, pixels_data);
end

local img
local w = MLX_WIN_WIDTH // 5
local h = MLX_WIN_HEIGHT // 5

function Setup(mlx, win)
	img = mlx_new_image(mlx, w, h)
	for y = 0, h - 1, 1 do
		for x = 0, w - 1, 1 do
			mlx_set_image_pixel(mlx, img, x, y, mlx_color:new(0xFF0F0FF0 + x * y * 2))
		end
	end
end

function Test(mlx, win)
	mlx_put_image_to_window(mlx, win, img, 50, 50)
end

function Cleanup(mlx, win)
	mlx_destroy_image(mlx, img)
end

local image
local w = MLX_WIN_WIDTH // 10
local h = MLX_WIN_HEIGHT // 10

function TestOnSetup(mlx, win)
	image = mlx_new_image(mlx, w, h)
	for y = 0, h - 1, 1 do
		for x = 0, w - 1, 1 do
			mlx_set_image_pixel(mlx, image, x, y, 0xFF0F0FF0 + x * y * 2)
		end
	end
end

function TestOnUpdate(mlx, win)
	for y = 0, 10, 1 do
		for x = 0, 10, 1 do
			mlx_put_image_to_window(mlx, win, image, x * w, y * h)
		end
	end
end

function TestOnQuit(mlx, win)
	mlx_destroy_image(mlx, image)
end

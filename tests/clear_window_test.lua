local image

function TestOnSetup(mlx, win)
	local dummy
	image = mlx_png_file_to_image(mlx, "resources/assets/logo.png", dummy, dummy)
end

function TestOnUpdate(mlx, win)
	mlx_string_put(mlx, win, 50, 50, 0xFFFFFFFF, "Example Text")
	mlx_put_image_to_window(mlx, win, image, 100, 0)
	for y = 0, 40, 1 do
		for x = 0, 40, 1 do
			mlx_pixel_put(mlx, win, x, y, 0xFFFF0000)
		end
	end
	mlx_clear_window(mlx, win)
	for y = 0, 40, 1 do
		for x = 0, 40, 1 do
			mlx_pixel_put(mlx, win, x + 100, y + 100, 0xFF00FF00)
		end
	end
end

function TestOnQuit(mlx, win)
	mlx_destroy_image(mlx, image)
end

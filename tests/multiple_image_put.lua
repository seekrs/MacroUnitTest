local image

function TestOnSetup(mlx, win)
	local dummy
	image = mlx_png_file_to_image(mlx, "resources/assets/logo.png", dummy, dummy);
end

function TestOnUpdate(mlx, win)
	mlx_put_image_to_window(mlx, win, image, 0, 0)
	mlx_put_image_to_window(mlx, win, image, 100, 0)
	mlx_put_image_to_window(mlx, win, image, 0, 100)
	mlx_put_image_to_window(mlx, win, image, 100, 100)
end

function TestOnQuit(mlx, win)
	mlx_destroy_image(mlx, image)
end



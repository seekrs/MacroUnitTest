local image

function TestOnSetup(mlx, win)
	local w
	local h
	image = mlx_png_file_to_image(mlx, "resources/assets/logo.png", w, h)
end

function TestOnUpdate(mlx, win)
	mlx_put_image_to_window(mlx, win, image, 20, 20)
end

function TestOnQuit(mlx, win)
	mlx_destroy_image(mlx, image)
end

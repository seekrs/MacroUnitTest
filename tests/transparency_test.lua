local image
local custom_image
local w = 42
local h = 42

function TestOnSetup(mlx, win)
	local dummy
	image = mlx_png_file_to_image(mlx, "resources/assets/logo.png", dummy, dummy)
	custom_image = mlx_new_image(mlx, w, h)
	for y = 0, h - 1, 1 do
		for x = 0, w - 1, 1 do
			mlx_set_image_pixel(mlx, custom_image, x, y, 0x990F0FF0 + x * y * 2)
		end
	end
end

function TestOnUpdate(mlx, win)
	mlx_put_image_to_window(mlx, win, image, 75, 75)
	mlx_put_image_to_window(mlx, win, custom_image, 200, 200)
	for y = 0, 40, 1 do
		for x = 0, 40, 1 do
			mlx_pixel_put(mlx, win, x + 100, y + 100, 0x55FF0000)
		end
	end
end

function TestOnQuit(mlx, win)
	mlx_destroy_image(mlx, image)
	mlx_destroy_image(mlx, custom_image)
end

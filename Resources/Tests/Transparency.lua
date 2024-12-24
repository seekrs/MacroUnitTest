local img
local custom_img
local w = 80
local h = 80

function Setup(mlx, win)
	local dummy = 0
	img = mlx_new_image_from_file(mlx, "Resources/Assets/Logo.png", dummy, dummy)
	custom_img = mlx_new_image(mlx, w, h)
	for y = 0, h - 1, 1 do
		for x = 0, w - 1, 1 do
			local color = mlx_color:new()
			color.rgba = 0x0F0FF099
			mlx_set_image_pixel(mlx, custom_img, x, y, color)
		end
	end
end

function Test(mlx, win)
	mlx_put_image_to_window(mlx, win, img, 75, 75)
	mlx_put_image_to_window(mlx, win, custom_img, 200, 200)
	for y = 0, 40, 1 do
		for x = 0, 40, 1 do
			local color = mlx_color:new()
			color.rgba = 0xFF000055
			mlx_pixel_put(mlx, win, x + 130, y + 130, color)
		end
	end
end

function Cleanup(mlx, win)
	mlx_destroy_image(mlx, img)
	mlx_destroy_image(mlx, custom_img)
end

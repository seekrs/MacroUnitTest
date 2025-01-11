local img
local custom_img
local w = 80
local h = 80

function Setup(mlx, win)
	local dummy = 0
	img = mlx_new_image_from_file(mlx, mlx_utils.get_current_working_directory() .. "Resources/Assets/Logo.png", dummy, dummy)
	custom_img = mlx_new_image(mlx, w, h)
	for y = 0, h - 1, 1 do
		for x = 0, w - 1, 1 do
			mlx_set_image_pixel(mlx, custom_img, x, y, mlx_color:new(0x0F0FF099))
		end
	end
end

function Test(mlx, win)
	mlx_put_image_to_window(mlx, win, img, 75, 75)
	mlx_put_image_to_window(mlx, win, custom_img, 200, 200)
	for y = 0, 40, 1 do
		for x = 0, 40, 1 do
			mlx_pixel_put(mlx, win, x + 130, y + 130, mlx_color:new(0xFF000055))
		end
	end
end

function Cleanup(mlx, win)
	mlx_destroy_image(mlx, img)
	mlx_destroy_image(mlx, custom_img)
end

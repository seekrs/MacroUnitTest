local img
local new_img
local w = 0
local h = 0

function Setup(mlx, win)
	img = mlx_new_image_from_file(mlx, mlx_utils.get_current_working_directory() .. "Resources/Assets/Logo.png", w, h)
	w = 200
	h = 200
	new_img = mlx_new_image(mlx, w, h)
	for y = 0, h - 1, 1 do
		for x = 0, w - 1, 1 do
			local color = mlx_get_image_pixel(mlx, img, x, y)
			mlx_set_image_pixel(mlx, new_img, x, y, color)
		end
	end
end

function Test(mlx, win)
	mlx_put_image_to_window(mlx, win, img, 0, 100)
	mlx_put_image_to_window(mlx, win, new_img, w, 100)
end

function Cleanup(mlx, win)
	mlx_destroy_image(mlx, new_img)
	mlx_destroy_image(mlx, img)
end

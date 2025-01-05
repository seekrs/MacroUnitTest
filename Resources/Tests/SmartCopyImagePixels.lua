local img
local new_img
local w = 0
local h = 0

function Setup(mlx, win)
	img = mlx_new_image_from_file(mlx, "Resources/Assets/Logo.png", w, h)
	w = 200
	h = 200
	new_img = mlx_new_image(mlx, w, h)
	local pixels = {}
	mlx_get_image_region(mlx, img, 0, 0, w, h, pixels)
	mlx_set_image_region(mlx, new_img, 0, 0, w, h, pixels)
end

function Test(mlx, win)
	mlx_put_image_to_window(mlx, win, img, 0, 100)
	mlx_put_image_to_window(mlx, win, new_img, w, 100)
end

function Cleanup(mlx, win)
	mlx_destroy_image(mlx, new_img)
	mlx_destroy_image(mlx, img)
end

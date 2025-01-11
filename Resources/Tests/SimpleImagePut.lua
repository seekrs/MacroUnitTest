local img
local dummy = 0

function Setup(mlx, win)
	img = mlx_new_image_from_file(mlx, mlx_utils.get_current_working_directory() .. "Resources/Assets/Logo.png", dummy, dummy)
end

function Test(mlx, win)
	mlx_put_image_to_window(mlx, win, img, 10, 10)
end

function Cleanup(mlx, win)
	mlx_destroy_image(mlx, img)
end

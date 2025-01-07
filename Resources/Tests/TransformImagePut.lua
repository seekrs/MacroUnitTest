local img
local dummy = 0

function Setup(mlx, win)
	img = mlx_new_image_from_file(mlx, "Resources/Assets/Logo.png", dummy, dummy)
end

function Test(mlx, win)
	mlx_put_transformed_image_to_window(mlx, win, img, 150, 60, 0.5, 0.5, 75)
	mlx_put_transformed_image_to_window(mlx, win, img, 100, 150, 0.1, 0.1, 130)
	mlx_put_transformed_image_to_window(mlx, win, img, 200, 200, 5, 5, 0)
end

function Cleanup(mlx, win)
	mlx_destroy_image(mlx, img)
end

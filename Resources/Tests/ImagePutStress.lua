local img
local dummy = 0

function Setup(mlx, win)
	img = mlx_new_image_from_file(mlx, mlx_utils.get_current_working_directory() .. "Resources/Assets/Logo.png", dummy, dummy)
end

function Test(mlx, win)
	local size = 42
	for y = 0, size, 1 do
		for x = 0, size, 1 do
			mlx_put_image_to_window(mlx, win, img, x * 3, y * 3)
		end
	end
	mlx_string_put(mlx, win, 10, 10, mlx_color:new(0xFFFFFFFF), "Number of image puts: " .. tostring(size * size))
end

function Cleanup(mlx, win)
	mlx_destroy_image(mlx, img)
end

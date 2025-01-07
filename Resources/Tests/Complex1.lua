local CIRCLE_RADIUS = 50
local CIRCLE_DIAMETER = CIRCLE_RADIUS + CIRCLE_RADIUS

local pixels_circle = {}

local img
local dummy = 0

function Setup(mlx, win)
	img = mlx_new_image_from_file(mlx, "Resources/Assets/Logo.png", dummy, dummy)

	local i = 1
	for y = 0, CIRCLE_DIAMETER do
		for x = 0, CIRCLE_DIAMETER do
			if (CIRCLE_RADIUS - y) * (CIRCLE_RADIUS - y) + (CIRCLE_RADIUS - x) * (CIRCLE_RADIUS - x) < CIRCLE_RADIUS * CIRCLE_RADIUS then
				pixels_circle[i] = mlx_color:new(0xA10000FF + ((y * x * (i - 1)) << 8));
			else
				pixels_circle[i] = mlx_color:new(0x00000000)
			end
			i = i + 1
		end
	end
end

function Test(mlx, win)
	local color_shift = 0
	for x = 0, MLX_WIN_WIDTH, 1 do
		mlx_pixel_put(mlx, win, MLX_WIN_HEIGHT - 1 - x, x, mlx_color:new(0x0000FFFF))
		mlx_pixel_put(mlx, win, x, x, mlx_color:new(0x0000FFFF + (color_shift << 24)))
		if color_shift < 255 then
			color_shift = color_shift + 1
		end
	end
	mlx_set_font_scale(mlx, "Resources/Fonts/OpenSans/OpenSans_Regular.ttf", 50.0)
	mlx_string_put(mlx, win, 50, 50, mlx_color:new(0xFFFF00FF), "this string is behind")
	mlx_put_image_to_window(mlx, win, img, 10, 10)
	mlx_set_font_scale(mlx, "Resources/Fonts/OpenSans/OpenSans_Regular.ttf", 36.0)
	mlx_string_put(mlx, win, 10, 20, mlx_color:new(0xFFFF00FF), "this is a string")
	mlx_set_font(mlx, "Resources/Fonts/OpenSans/OpenSans_Italic.ttf")
	mlx_string_put(mlx, win, 50, 50, mlx_color:new(0xFF0000FF), "macro unit tester")
	for y = 0, 40, 1 do
		for x = 0, 40, 1 do
			mlx_pixel_put(mlx, win, 180 + x, 180 + y, mlx_color:new(0xFF0000FF))
		end
	end
	mlx_string_put(mlx, win, 50, 80, mlx_color:new(0xF00FFFFF), "this string is in middle")
	mlx_put_transformed_image_to_window(mlx, win, img, 150, 60, 0.5, 0.5, 75)
	mlx_put_transformed_image_to_window(mlx, win, img, 190, 190, 0.1, 0.1, 130)
	mlx_string_put(mlx, win, 50, 110, mlx_color:new(0xF00F44FF), "this string is on top")
	mlx_pixel_put_region(mlx, win, 200, 170, CIRCLE_DIAMETER + 1, CIRCLE_DIAMETER, pixels_circle);
	mlx_set_font_scale(mlx, "default", 32.0)
	mlx_string_put(mlx, win, 150, 250, mlx_color:new(0x0000FFFF), "yes")
	mlx_set_font_scale(mlx, "Resources/Fonts/OpenSans/OpenSans_ExtraBold.ttf", 45.0)
	mlx_string_put(mlx, win, 10, 350, mlx_color:new(0xB4A8FFFFF), "another string")
	for y = 0, 40, 1 do
		for x = 0, 40, 1 do
			mlx_pixel_put(mlx, win, x + 130, y + 130, mlx_color:new(0xFF000055))
		end
	end
end

function Cleanup(mlx, win)
	mlx_destroy_image(mlx, img)
end

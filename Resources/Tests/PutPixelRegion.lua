local CIRCLE_RADIUS = 50
local CIRCLE_DIAMETER = CIRCLE_RADIUS + CIRCLE_RADIUS

local pixels_circle = {}

function Setup(mlx, win)
	local i = 1
	for y = 0, CIRCLE_DIAMETER do
		for x = 0, CIRCLE_DIAMETER do
			if (CIRCLE_RADIUS - y) * (CIRCLE_RADIUS - y) + (CIRCLE_RADIUS - x) * (CIRCLE_RADIUS - x) < CIRCLE_RADIUS * CIRCLE_RADIUS then
				pixels_circle[i] = mlx_color:new(0xA10000FF + ((y * x * (i - 1)) << 8));
			else
				pixels_circle[i] = mlx_color:new(0x000000FF)
			end
			i = i + 1
		end
	end
end

function Test(mlx, win)
	mlx_pixel_put_region(mlx, win, 200, 170, CIRCLE_DIAMETER + 1, CIRCLE_DIAMETER, pixels_circle);
end

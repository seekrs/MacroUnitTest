function TestOnSetup(mlx, win)
	mlx_set_font_scale(mlx, win, "resources/fonts/opensans/OpenSans-Regular.ttf", 36)
end

function TestOnUpdate(mlx, win)
	mlx_string_put(mlx, win, 50, 50, 0xFFFFFFFF, "Example Text")
end


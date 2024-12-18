function TestOnSetup(mlx, win)
	mlx_set_font(mlx, win, "resources/fonts/opensans/OpenSans-Regular.ttf")
end

function TestOnUpdate(mlx, win)
	mlx_string_put(mlx, win, 50, 50, 0xFFFFFFFF, "Example Text")
end


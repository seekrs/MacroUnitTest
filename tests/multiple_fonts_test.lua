
function TestOnUpdate(mlx, win)
	mlx_string_put(mlx, win, 10, 100, 0xFFFF00FF, "MacroLibX")
	mlx_set_font_scale(mlx, win, "resources/fonts/opensans/OpenSans-Regular.ttf", 36)
	mlx_string_put(mlx, win, 200, 110, 0xFFFFFFFF, "Example Text")
	mlx_set_font_scale(mlx, win, "resources/fonts/opensans/OpenSans-Bold.ttf", 50)
	mlx_string_put(mlx, win, 10, 300, 0xFFFF0000, "youpi")
	mlx_set_font_scale(mlx, win, "resources/fonts/opensans/OpenSans-LightItalic.ttf", 25)
	mlx_string_put(mlx, win, 0, 200, 0xFF00FFFF, "pouic")
	mlx_set_font_scale(mlx, win, "resources/fonts/opensans/OpenSans-ExtraBold.ttf", 62)
	mlx_string_put(mlx, win, 100, 50, 0xFFFF00FF, "42angouleme")
end


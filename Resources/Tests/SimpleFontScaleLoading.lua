function Test(mlx, win)
	mlx_set_font_scale(mlx, "Resources/Fonts/OpenSans/OpenSans_Regular.ttf", 50.0)
	mlx_string_put(mlx, win, 50, 50, mlx_color:new(0xFFFF00FF), "this is a string")
end

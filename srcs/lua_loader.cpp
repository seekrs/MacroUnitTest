/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lua_loader.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 22:38:54 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/28 00:22:32 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lua_loader.h>
#include <loader/loader.h>
#include <optional>

namespace mlxut
{
	LuaLoader::LuaLoader() : _state()
	{
		_state.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math, sol::lib::table, sol::lib::os, sol::lib::string);

		// bind mlx functions
		_state.set_function("mlx_new_window", [](void* mlx, int w, int h, std::string title)
		{
			return mlx_new_window(mlx, w, h, title.c_str());
		});

		_state.set_function("mlx_pixel_put", [](void* mlx, void* win, int x, int y, int color)
		{
			return mlx_pixel_put(mlx, win, x, y, color);
		});

		_state.set_function("mlx_new_image", [](void* mlx, int w, int h)
		{
			return mlx_new_image(mlx, w, h);
		});

		_state.set_function("mlx_get_image_pixel", [](void* mlx, void* img, int x, int y)
		{
			return mlx_get_image_pixel(mlx, img, x, y);
		});

		_state.set_function("mlx_set_image_pixel", [](void* mlx, void* img, int x, int y, int color)
		{
			mlx_set_image_pixel(mlx, img, x, y, color);
		});

		_state.set_function("mlx_put_image_to_window", [](void* mlx, void* win, void* img, int x, int y)
		{
			return mlx_put_image_to_window(mlx, win, img, x, y);
		});

		_state.set_function("mlx_destroy_image", [](void* mlx, void* img)
		{
			return mlx_destroy_image(mlx, img);
		});

		_state.set_function("mlx_png_file_to_image", [](void* mlx, std::string file, int* w, int* h)
		{
			return mlx_png_file_to_image(mlx, file.data(), w, h);
		});

		_state.set_function("mlx_jpg_file_to_image", [](void* mlx, std::string file, int* w, int* h)
		{
			return mlx_jpg_file_to_image(mlx, file.data(), w, h);
		});

		_state.set_function("mlx_bmp_file_to_image", [](void* mlx, std::string file, int* w, int* h)
		{
			return mlx_bmp_file_to_image(mlx, file.data(), w, h);
		});

		_state.set_function("mlx_string_put", [](void* mlx, void* win, int x, int y, int color, std::string str)
		{
			return mlx_string_put(mlx, win, x, y, color, str.data());
		});

		_state.set_function("mlx_set_font", [](void* mlx, void* win, std::string font)
		{
			mlx_set_font(mlx, win, font.data());
		});

		_state.set_function("mlx_set_font_scale", [](void* mlx, void* win, std::string font, float scale)
		{
			mlx_set_font_scale(mlx, win, font.data(), scale);
		});

		_state.set_function("mlx_clear_window", [](void* mlx, void* win)
		{
			return mlx_clear_window(mlx, win);
		});

		_state.set_function("mlx_get_screens_size", [](void* mlx, int* w, int* h)
		{
			return mlx_get_screens_size(mlx, w, h);
		});
	}

	std::optional<LuaScript> LuaLoader::loadScript(const std::filesystem::path& lua_file)
	{
		if(!std::filesystem::exists(lua_file))
		{
			std::cerr << "Lua Loader : invalid script path " << lua_file << std::endl;;
			return std::nullopt;
		}

		sol::environment env(_state, sol::create, _state.globals());

		auto sol_script = _state.script_file(lua_file.string(), env, sol::script_pass_on_error);
		if(!sol_script.valid())
		{
			sol::error err = sol_script;
			std::cerr << "Lua Error : " << err.what() << std::endl;
			std::cerr << "Lua Loader : failed to load and execute Lua script " << lua_file << std::endl;
			return std::nullopt;
		}

		std::optional<LuaScript> script;
		script.emplace();

		script->_env = std::move(env);

		script->_on_setup = script->_env["TestOnSetup"];
		script->_on_update = script->_env["TestOnUpdate"];
		script->_on_quit = script->_env["TestOnQuit"];

		_state.collect_garbage();

		return script;
	}

}

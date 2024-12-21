#include <Scripting/Loader.h>
#include <Loader/Loader.h>
#include <Utils/Ansi.h>

namespace mlxut
{
	LuaLoader::LuaLoader() : m_state()
	{
		m_state.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math, sol::lib::table, sol::lib::os, sol::lib::string);

		m_state.set("MLX_WIN_WIDTH", MLX_WIN_WIDTH);
		m_state.set("MLX_WIN_HEIGHT", MLX_WIN_HEIGHT);

		auto color_type = m_state.new_usertype<mlx_color>("mlx_color");
		color_type["rgba"] = sol::property(&mlx_color::GetRGBA, &mlx_color::SetRGBA);
		color_type["r"] = sol::property(&mlx_color::GetR, &mlx_color::SetR);
		color_type["g"] = sol::property(&mlx_color::GetG, &mlx_color::SetG);
		color_type["b"] = sol::property(&mlx_color::GetB, &mlx_color::SetB);
		color_type["a"] = sol::property(&mlx_color::GetA, &mlx_color::SetA);

		#define MLX_UT_MLX_FUNCTION(fn) m_state.set_function(#fn, MLXLoader::Get().fn);
			#define MLX_UT_ONLY_TESTS_FUNCTION
				#include <Loader/Prototypes.h>
			#undef MLX_UT_ONLY_TESTS_FUNCTION
		#undef MLX_UT_MLX_FUNCTION
	}

	std::optional<LuaScript> LuaLoader::LoadScript(std::filesystem::path lua_file)
	{
		if(!std::filesystem::exists(lua_file))
		{
			std::cerr << Ansi::red << "Error: " << Ansi::def << "Lua Loader: invalid script path " << lua_file << std::endl;
			return std::nullopt;
		}

		sol::environment env(m_state, sol::create, m_state.globals());

		auto sol_script = m_state.script_file(lua_file.string(), env, sol::script_pass_on_error);
		if(!sol_script.valid())
		{
			sol::error err = sol_script;
			std::cerr << Ansi::red << "Error: " << Ansi::def << "Lua Error: " << err.what() << std::endl;
			std::cerr << Ansi::red << "Error: " << Ansi::def << "Failed to load and execute Lua script" << std::endl;
			return std::nullopt;
		}

		std::optional<LuaScript> script;
		script.emplace();

		script->m_env = std::move(env);

		script->f_on_setup = script->m_env["Setup"];
		script->f_on_test = script->m_env["Test"];
		script->f_on_quit = script->m_env["Cleanup"];

		m_state.collect_garbage();

		return script;
	}
}

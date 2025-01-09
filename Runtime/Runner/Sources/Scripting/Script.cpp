#include <Scripting/Script.h>
#include <Utils/Ansi.h>

namespace mlxut
{
	void LuaScript::RunOnSetup(mlx_context mlx, mlx_window window)
	{
		if(!f_on_setup.valid())
			return;
		sol::protected_function_result result = f_on_setup(mlx, window);
		if(!result.valid())
		{
			sol::error err = result;
			std::cerr << Ansi::red << "Error: " << Ansi::def << "Lua Script: failed to execute setup function: " << err.what() << std::endl;
			m_has_failed = true;
		}
	}

	void LuaScript::RunOnTest(mlx_context mlx, mlx_window window)
	{
		if(!f_on_test.valid())
			return;
		sol::protected_function_result result = f_on_test(mlx, window);
		if(!result.valid())
		{
			sol::error err = result;
			std::cerr << Ansi::red << "Error: " << Ansi::def << "Lua Error: failed to execute update function: " << err.what() << std::endl;
			m_has_failed = true;
		}
	}

	void LuaScript::RunOnQuit(mlx_context mlx, mlx_window window)
	{
		if(!f_on_quit.valid())
			return;
		sol::protected_function_result result = f_on_quit(mlx, window);
		if(!result.valid())
		{
			sol::error err = result;
			std::cerr << Ansi::red << "Error: " << Ansi::def << "Lua Error: failed to execute quit function: " << err.what() << std::endl;
			m_has_failed = true;
		}
	}
}

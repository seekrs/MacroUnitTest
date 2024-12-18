#include <lua_script.h>

namespace mlxut
{
	void LuaScript::runOnSetup(void* mlx, void* win)
	{
		if(!_on_setup.valid())
			return;
		sol::protected_function_result result = _on_setup(mlx, win);
		if(!result.valid())
		{
			sol::error err = result;
			std::cerr << "\033[1;31mLua Script : \033[1;0mfailed to execute setup function : " << err.what() << std::endl;
			_failed = true;
		}
	}

	void LuaScript::runOnUpdate(void* mlx, void* win)
	{
		if(!_on_update.valid())
			return;
		sol::protected_function_result result = _on_update(mlx, win);
		if(!result.valid())
		{
			sol::error err = result;
			std::cerr << "\033[1;31mLua Script : \033[1;0mfailed to execute update function : " << err.what() << std::endl;
			_failed = true;
		}
	}

	void LuaScript::runOnQuit(void* mlx, void* win)
	{
		if(!_on_quit.valid())
			return;
		sol::protected_function_result result = _on_quit(mlx, win);
		if(!result.valid())
		{
			sol::error err = result;
			std::cerr << "\033[1;31mLua Script : \033[1;0mfailed to execute quit function : " << err.what() << std::endl;
			_failed = true;
		}
	}
}

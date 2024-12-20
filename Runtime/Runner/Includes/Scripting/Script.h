#ifndef MLX_UT_LUA_SCRIPT
#define MLX_UT_LUA_SCRIPT

#include <PreCompiled.h>
#include <Loader/PFN.h>

namespace mlxut
{
	class LuaScript
	{
		friend class LuaLoader;

		public:
			LuaScript() = default;

			void RunOnSetup(mlx_context mlx, mlx_window window);
			void RunOnTest(mlx_context mlx, mlx_window window);
			void RunOnQuit(mlx_context mlx, mlx_window window);

			inline bool HasFailed() const noexcept { return m_has_failed; }

			~LuaScript() = default;

		private:
			sol::environment m_env;
			sol::protected_function f_on_setup;
			sol::protected_function f_on_test;
			sol::protected_function f_on_quit;
			bool m_has_failed = false;
	};
}

#endif

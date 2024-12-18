#ifndef MLX_UT_LUA_SCRIPT
#define MLX_UT_LUA_SCRIPT

#include <Pch.h>

namespace mlxut
{
	class LuaScript
	{
		friend class LuaLoader;

		public:
			LuaScript() = default;

			void RunOnSetup(void* mlx, void* win);
			void RunOnUpdate(void* mlx, void* win);
			void RunOnQuit(void* mlx, void* win);

			inline bool Failed() const noexcept { return m_has_failed; }

			~LuaScript() = default;

		private:
			sol::environment m_env;
			sol::protected_function m_on_setup;
			sol::protected_function m_on_update;
			sol::protected_function m_on_quit;
			bool m_has_failed = false;
	};
}

#endif

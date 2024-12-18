#ifndef MLX_UT_LUA_LOADER
#define MLX_UT_LUA_LOADER

#include <Pch.h>
#include <Scripting/LuaScript.h>

namespace mlxut
{
	class LuaLoader
	{
		public:
			LuaLoader();

			std::optional<LuaScript> LoadScript(const std::filesystem::path& path);

			~LuaLoader() = default;

		private:
			sol::state m_state;
	};
}

#endif

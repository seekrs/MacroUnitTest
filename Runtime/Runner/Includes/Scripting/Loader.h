#ifndef MLX_UT_LUA_LOADER
#define MLX_UT_LUA_LOADER

#include <PreCompiled.h>
#include <Scripting/Script.h>

namespace mlxut
{
	class LuaLoader
	{
		public:
			LuaLoader();
			std::optional<LuaScript> LoadScript(std::filesystem::path path);
			~LuaLoader() = default;

		private:
			sol::state m_state;
	};
}

#endif

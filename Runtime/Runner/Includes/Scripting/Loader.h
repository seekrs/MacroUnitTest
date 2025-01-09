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

			#ifndef MLX_UT_EMBED_TESTS
				std::optional<LuaScript> LoadScript(std::filesystem::path path);
			#else
				std::optional<LuaScript> LoadScript(std::string name);
			#endif

			~LuaLoader() = default;

		private:
			sol::state m_state;
	};
}

#endif

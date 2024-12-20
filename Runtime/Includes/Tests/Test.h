#ifndef MLX_UT_TEST
#define MLX_UT_TEST

#include <PreCompiled.h>
#include <Scripting/Script.h>

namespace mlxut
{
	class Test
	{
		public:

		private:
			LuaScript m_script;
			std::vector<std::uint32_t> m_result_pixels;
			SDL_Texture* p_reference = nullptr;
			SDL_Texture* p_result = nullptr;
			mlx_context m_mlx;
			mlx_window m_window;
	};
}

#endif

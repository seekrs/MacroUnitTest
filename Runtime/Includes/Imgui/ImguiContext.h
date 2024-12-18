#ifndef MLX_UT_IMGUI_CONTEXT
#define MLX_UT_IMGUI_CONTEXT

#include <Pch.h>

namespace mlxut
{
	class ImGuiContext
	{
		public:
			ImGuiContext(const class Window& win, const class Renderer& renderer);

			void CheckEvents(const SDL_Event* event) noexcept;
			void BeginFrame() noexcept;
			void EndFrame() noexcept;
			void Destroy() noexcept;

			~ImGuiContext();

			static void SetDarkTheme();
			static void SetWhiteTheme();
			static void SetDraculaTheme();
			static void SetCosyTheme();

		private:
			const class Renderer& m_renderer;
	};
}

#endif

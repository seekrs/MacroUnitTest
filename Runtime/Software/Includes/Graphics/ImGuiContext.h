#ifndef MLX_UT_IMGUI_CONTEXT
#define MLX_UT_IMGUI_CONTEXT

#include <PreCompiled.h>
#include <Graphics/Renderer.h>

namespace mlxut
{
	class ImGuiContext
	{
		public:
			ImGuiContext(const Window& win, const Renderer& renderer);

			void CheckEvents(const SDL_Event* event) noexcept;
			void BeginFrame() noexcept;
			void EndFrame() noexcept;

			~ImGuiContext();

			static void SetDarkTheme();
			static void SetWhiteTheme();
			static void SetDraculaTheme();
			static void SetCosyTheme();

		private:
			const Renderer& m_renderer;
	};
}

#endif

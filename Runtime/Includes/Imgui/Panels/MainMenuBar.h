#ifndef MLX_UT_MAIN_MENU_BAR
#define MLX_UT_MAIN_MENU_BAR

#include <Pch.h>

namespace mlxut
{
	class MainMenuBar
	{
		public:
			MainMenuBar(const class Renderer& renderer, NonOwningPtr<class Tester> tester);
			void Render(const class Window& win, ivec2 size) noexcept;
			void RenderAboutWindow(ivec2 size);
			inline bool ShouldRenderAboutWindow() const noexcept { return m_render_about_window; }
			inline bool QuitRequested() const noexcept { return m_quit_requested; }
			void Destroy() noexcept;
			~MainMenuBar();

		private:
			const class Renderer& m_renderer;
			NonOwningPtr<class Tester> p_tester;
			SDL_Texture* p_logo;
			bool m_render_about_window = false;
			bool m_quit_requested = false;
	};
}

#endif

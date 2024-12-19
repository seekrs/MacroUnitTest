#ifndef MLX_UT_APPLICATION
#define MLX_UT_APPLICATION

#include <Graphics/Window.h>
#include <Graphics/Renderer.h>
#include <Graphics/ImGuiContext.h>
#include <Graphics/MenuBar.h>
#include <Graphics/PanelStack.h>
#include <Core/Loader/Loader.h>

namespace mlxut
{
	class Application
	{
		public:
			Application();
			void Run();
			~Application();

		private:
			void LoadSystemCursors() noexcept;
			void UpdateCursor() noexcept;

		private:
			MLXLoader m_loader;
			std::unordered_map<SDL_SystemCursor, SDL_Cursor*> m_cursors;
			MenuBar m_menubar;
			PanelStack m_stack;
			SDL_Event m_event;
			std::unique_ptr<Window> p_window;
			std::unique_ptr<Renderer> p_renderer;
			std::unique_ptr<ImGuiContext> p_imgui;
	};
}

#endif

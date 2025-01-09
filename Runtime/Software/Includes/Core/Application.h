#ifndef MLX_UT_APPLICATION
#define MLX_UT_APPLICATION

#include <Graphics/Window.h>
#include <Graphics/Renderer.h>
#include <Graphics/ImGuiContext.h>
#include <Graphics/MenuBar.h>
#include <Graphics/PanelStack.h>
#include <Tests/Tester.h>

namespace mlxut
{
	class Application
	{
		public:
			Application();

			void Run();
			inline void SetCursor(SDL_SystemCursor cursor) const noexcept { SDL_SetCursor(m_cursors.at(cursor)); }
			[[nodiscard]] inline MouseWheelEvent GetMouseWheelEvent() const noexcept { return m_wheel_event; }

			inline static Application& Get() noexcept { return *s_instance; }

			~Application();

		private:
			void LoadSystemCursors() noexcept;
			void UpdateCursor() noexcept;

		private:
			inline static Application* s_instance = nullptr;

			Tester m_tester;
			std::unordered_map<SDL_SystemCursor, SDL_Cursor*> m_cursors;
			MenuBar m_menubar;
			PanelStack m_stack;
			SDL_Event m_event;
			std::unique_ptr<Window> p_window;
			std::unique_ptr<Renderer> p_renderer;
			std::unique_ptr<ImGuiContext> p_imgui;
			MouseWheelEvent m_wheel_event = MouseWheelEvent::Idle;
	};
}

#endif

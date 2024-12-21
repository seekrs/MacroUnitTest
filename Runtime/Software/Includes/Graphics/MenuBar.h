#ifndef MLX_UT_MENU_BAR
#define MLX_UT_MENU_BAR

#include <PreCompiled.h>
#include <Core/FileDialog.h>

namespace mlxut
{
	class MenuBar
	{
		public:
			MenuBar();

			void Render(const class Window& win, ImVec2 size) noexcept;
			void RenderAboutWindow();
			void RenderSettingsWindow();

			[[nodiscard]] inline bool ShouldRenderAboutWindow() const noexcept { return m_render_about_window; }
			[[nodiscard]] inline bool ShouldRenderSettingsWindow() const noexcept { return m_render_settings_window; }
			[[nodiscard]] inline bool ShouldStartAllTests() const noexcept { return m_launch_all_tests; }
			[[nodiscard]] inline bool IsQuitRequested() const noexcept { return m_quit_requested; }
			[[nodiscard]] inline float GetHeight() const noexcept { return m_height; }
			[[nodiscard]] inline const std::filesystem::path& GetMLXPath() const noexcept { return m_mlx_lib_path; }

			~MenuBar() = default;

		private:
			void RenderGeneralSettings();

		private:
			std::filesystem::path m_mlx_lib_path;
			FileDialog m_dialog;
			float m_height;
			bool m_render_about_window = false;
			bool m_render_settings_window = false;
			bool m_launch_all_tests = false;
			bool m_quit_requested = false;
	};
}

#endif

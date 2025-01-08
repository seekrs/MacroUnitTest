#ifndef MLX_UT_SCRIPT_PANEL
#define MLX_UT_SCRIPT_PANEL

#include <Graphics/Panels/Panel.h>
#include <Graphics/TextEditor.h>

namespace mlxut
{
	class ScriptPanel : public Panel
	{
		public:
			ScriptPanel(class Renderer& renderer, class Tester& tester);

			void OnUpdate(ImVec2 size) override;

			inline void SetFont(ImFont* font) noexcept { p_font = font; }

			~ScriptPanel() override = default;

		private:
			TextEditor m_editor;
			TextEditor::LanguageDefinition m_lang;
			class Tester& m_tester;
			ImFont* p_font = nullptr;
	};
}

#endif

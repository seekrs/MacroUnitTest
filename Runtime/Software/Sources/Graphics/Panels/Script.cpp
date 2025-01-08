#include "SDL_surface.h"
#include <Graphics/Panels/Script.h>
#include <Core/OS/OSInstance.h>
#include <Core/MaterialFont.h>
#include <Tests/Tester.h>
#include <Graphics/Renderer.h>

#ifdef MLX_UT_RELEASE
	#include <Embedded/Fonts.h>
	#include <Embedded/Tests.h>
#endif

namespace mlxut
{
	const TextEditor::Palette& GetPalette()
	{
		const static TextEditor::Palette p = { {
			0xff7f7f7f,	// Default
			0xffc086c5,	// Keyword
			0xffa8ceb5,	// Number
			0xff7991ce,	// String
			0xff7991ce,	// Char literal
			0xffffffff, // Punctuation
			0xff408080,	// Preprocessor
			0xffd4d4d4, // Identifier
			0xffd69c56, // Known identifier
			0xffd69c56, // Preproc identifier
			0xff4d8a5f, // Comment (single line)
			0xff4d8a5f, // Comment (multi line)
			0xff171717, // Background
			0xffe0e0e0, // Cursor
			0x80a06020, // Selection
			0x800020ff, // ErrorMarker
			0x40f08000, // Breakpoint
			0xff595554, // Line number
			0x40000000, // Current line fill
			0x40808080, // Current line fill (inactive)
			0x40a0a0a0, // Current line edge
		} };
		return p;
	}

	ScriptPanel::ScriptPanel(Renderer& renderer, Tester& tester) : Panel("Script"), m_tester(tester)
	{
		m_lang = TextEditor::LanguageDefinition::Lua();
		m_lang.mAutoIndentation = true;

		#define MLX_UT_MLX_FUNCTION(fn) #fn,

		std::array identifiers = {
			"Test", "Setup", "Cleanup", "mlx_color", "MLX_WIN_WIDTH", "MLX_WIN_HEIGHT",
			#include <Loader/Prototypes.h>
		};

		#undef MLX_UT_MLX_FUNCTION
		for(const char* str : identifiers)
		{
			TextEditor::Identifier id;
			id.mDeclaration = "Built-ins";
			m_lang.mIdentifiers.insert(std::make_pair(std::string(str), id));
		}

		m_editor.SetLanguageDefinition(m_lang);

		m_editor.SetTabSize(4);
		m_editor.SetShowWhitespaces(false);
		m_editor.SetPalette(GetPalette());
		m_editor.SetReadOnly(true);

		for(std::size_t size = 10; size < 28; size += 2)
		{
			#ifndef MLX_UT_RELEASE
				ImFont* font = ImGui::GetIO().Fonts->AddFontFromFileTTF((OSInstance::Get().GetCurrentWorkingDirectoryPath() / "Resources/Fonts/Sono_Medium.ttf").string().c_str(), size);
			#else
				ImFont* font = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(reinterpret_cast<void*>(const_cast<std::uint8_t*>(Sono_Medium_data.data())), Sono_Medium_data.size(), size);
			#endif

			if(size == 12)
				p_font = font;
		}
	}

	void ScriptPanel::OnUpdate(ImVec2 size)
	{
		static const std::string* test_name_ptr = nullptr;

		if(ImGui::Begin(MLX_UT_ICON_MD_CODE" Script", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
		{
			auto test = m_tester.GetAllTests()[m_tester.GetSelectedTest()];

			if(test_name_ptr != &test->GetName())
			{
				#ifndef MLX_UT_RELEASE
				{
					std::ifstream file(OSInstance::Get().GetCurrentWorkingDirectoryPath() / "Resources/Tests" / (test->GetName() + ".lua"));
					if(file.good())
					{
						std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
						m_editor.SetText(str);
					}
				}
				#else
					m_editor.SetText(GetDataFromFilename(test->GetName()));
				#endif
				test_name_ptr = &test->GetName();
			}

			TextEditor::ErrorMarkers markers;

			if(test->HasFailed() && !test->GetLuaErrorMessage().empty()) // TODO: dont update each frame
				markers[test->GetLuaErrorLine()] = test->GetLuaErrorMessage();

			m_editor.SetErrorMarkers(markers);

			ImGui::PushFont(p_font);
				m_editor.Render("Code", ImVec2(), true);
			ImGui::PopFont();
			ImGui::End();
		}
	}
}

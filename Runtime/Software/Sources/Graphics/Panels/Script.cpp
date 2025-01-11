#include "imgui.h"
#include <Graphics/Panels/Script.h>
#include <Core/OS/OSInstance.h>
#include <Core/MaterialFont.h>
#include <Tests/Tester.h>
#include <Graphics/Renderer.h>
#include <Core/Application.h>
#include <filesystem>

#ifdef MLX_UT_RELEASE
	#include <Embedded/Fonts.h>
#endif
#ifdef MLX_UT_EMBED_TESTS
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
			"mlx_utils", "get_current_working_directory",
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
		#ifdef MLX_UT_EMBED_TESTS
			m_editor.SetReadOnly(true);
		#endif

		for(std::size_t size = 10; size < 28; size += 2)
		{
			#ifndef MLX_UT_RELEASE
				ImFont* font = ImGui::GetIO().Fonts->AddFontFromFileTTF((OSInstance::Get().GetCurrentWorkingDirectoryPath() / "Resources/Fonts/Sono_Medium.ttf").string().c_str(), size);
			#else
				ImFont* font = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(reinterpret_cast<void*>(const_cast<std::uint8_t*>(Sono_Medium_data.data())), Sono_Medium_data.size(), size);
			#endif

			if(size == 12)
			{
				p_font = font;
				m_font_id = ImGui::GetIO().Fonts->Fonts.size() - 1;
			}
		}
	}

	void ScriptPanel::OnUpdate(ImVec2 size)
	{
		static const std::string* test_name_ptr = nullptr;
		#ifndef MLX_UT_EMBED_TESTS
			static std::filesystem::file_time_type last_write{};
			static bool unsaved = false;
		#endif
		static TextEditor::ErrorMarkers markers;

		if(ImGui::Begin(MLX_UT_ICON_MD_CODE" Script", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
		{
			auto test = m_tester.GetAllTests()[m_tester.GetSelectedTest()];

			#ifndef MLX_UT_EMBED_TESTS
				std::filesystem::path file_path = OSInstance::Get().GetCurrentWorkingDirectoryPath() / "Resources/Tests" / (test->GetName() + ".lua");
				if(test_name_ptr != &test->GetName() || std::filesystem::last_write_time(file_path) != last_write)
			#else
				if(test_name_ptr != &test->GetName())
			#endif
			{
				#ifndef MLX_UT_EMBED_TESTS
					last_write = std::filesystem::last_write_time(file_path);
					{
						std::ifstream file(std::move(file_path));
						if(file.good())
						{
							std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
							str.pop_back();
							m_editor.SetText(str);
						}
					}
				#else
					m_editor.SetText(GetDataFromFilename(test->GetName()));
				#endif
				test_name_ptr = &test->GetName();
				markers.clear();
				test->ClearLuaErrors();
			}

			if(!m_tester.AreTestsRunning())
				markers.clear();
			if(markers.empty() && m_tester.HaveAllTestsFinished() && test->HasFailed() && !test->GetLuaErrorMessage().empty())
				markers[test->GetLuaErrorLine()] = test->GetLuaErrorMessage();

			m_editor.SetErrorMarkers(markers);

			if(ImGui::IsKeyDown(ImGuiKey_LeftCtrl) || ImGui::IsKeyDown(ImGuiKey_RightCtrl))
			{
				ImGuiIO& io = ImGui::GetIO();

				if((ImGui::IsKeyPressed(ImGuiKey_Equal) || ImGui::IsKeyPressed(ImGuiKey_KeypadAdd) || Application::Get().GetMouseWheelEvent() == MouseWheelEvent::Up)
					&& m_font_id < io.Fonts->Fonts.size() - 1)
				{
					p_font = io.Fonts->Fonts[m_font_id + 1];
					m_font_id++;
				}
				if((ImGui::IsKeyPressed(ImGuiKey_Minus) || ImGui::IsKeyPressed(ImGuiKey_KeypadSubtract) || Application::Get().GetMouseWheelEvent() == MouseWheelEvent::Down)
					&& m_font_id > io.Fonts->Fonts.size() / 2)
				{
					p_font = io.Fonts->Fonts[m_font_id - 1];
					m_font_id--;
				}
			}

			ImGui::PushFont(p_font);
				m_editor.Render("Code", ImVec2(), true);
			ImGui::PopFont();

			#ifndef MLX_UT_EMBED_TESTS
				if(m_editor.IsTextChanged())
					unsaved = true;
				if(unsaved)
				{
					ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() - 60, 40));
					bool save = false;
					if(ImGui::BeginChild("#test", ImVec2(0.0f, 0.0f), 0, ImGuiWindowFlags_NoBackground))
					{
						if(ImGui::Button(MLX_UT_ICON_MD_SAVE))
							save = true;
						ImGui::EndChild();
					}
					if(ImGui::IsKeyChordPressed(ImGuiMod_Ctrl | ImGuiKey_S))
						save = true;

					if(save)
					{
						std::ofstream file(OSInstance::Get().GetCurrentWorkingDirectoryPath() / "Resources/Tests" / (test->GetName() + ".lua"));
						if(file.good())
							file << m_editor.GetText();
						unsaved = false;
					}
				}
			#endif

			ImGui::End();
		}
	}
}

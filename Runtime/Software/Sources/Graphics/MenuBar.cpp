#include <Core/Application.h>
#include <Graphics/MenuBar.h>
#include <Graphics/ImGuiContext.h>
#include <Graphics/Window.h>
#include <Graphics/Renderer.h>
#include <Core/MaterialFont.h>
#include <Core/OS/OSInstance.h>
#include <Core/CLI.h>

#ifdef MLX_UT_RELEASE
	#include <Embedded/Logo.h>
#endif

namespace mlxut
{
	MenuBar::MenuBar()
	{
		auto mlx_path = CommandLineInterface::Get().GetOption("path");
		if(mlx_path.has_value())
			m_mlx_lib_path = *mlx_path;
	}

	void MenuBar::Render(const Window& win, const Renderer& renderer, ImVec2 size, Tester& tester) noexcept
	{
		ImGuiStyle* style = &ImGui::GetStyle();

		if(p_logo == nullptr)
		{
			#ifndef MLX_UT_RELEASE
				p_logo = IMG_LoadTexture(renderer.Get(), (OSInstance::Get().GetCurrentWorkingDirectoryPath() / "Resources/Assets/Logo.png").string().c_str());
			#else
				SDL_RWops* rw = SDL_RWFromMem(reinterpret_cast<void*>(const_cast<std::uint8_t*>(logo_data.data())), logo_data.size());
				SDL_Surface* surface = IMG_Load_RW(rw, 1);
				p_logo = SDL_CreateTextureFromSurface(renderer.Get(), surface);
				SDL_FreeSurface(surface);
			#endif
		}

		static bool dialog_openned = false;
		#ifndef MLX_UT_EMBED_TESTS
			static bool new_test_openned = false;
		#endif

		if(dialog_openned && m_dialog.IsFinished())
		{
			m_mlx_lib_path = m_dialog.GetResult();
			dialog_openned = false;
		}

		m_launch_all_tests = false;

		if(ImGui::BeginMainMenuBar())
		{
			ImGui::Image(reinterpret_cast<void*>(p_logo), ImVec2{ 20.0f, 20.0f });
			if(ImGui::BeginMenu(MLX_UT_ICON_MD_FOLDER" File"))
			{
				if(ImGui::MenuItem("Open") && !dialog_openned)
				{
					m_dialog.Open("Select lib mlx", { "dynamic library (" MLX_UT_LIB_EXTENSION ")", "*" MLX_UT_LIB_EXTENSION });
					dialog_openned = true;
				}
				if(ImGui::MenuItem("Quit"))
					m_quit_requested = true;
				ImGui::EndMenu();
			}
			if(ImGui::BeginMenu(MLX_UT_ICON_MD_TUNE" Edit"))
			{
				#ifndef MLX_UT_EMBED_TESTS
					if(ImGui::MenuItem("Create new test"))
						new_test_openned = true;
				#endif
				if(ImGui::MenuItem("Settings"))
					m_render_settings_window = true;
				ImGui::EndMenu();
			}
			if(ImGui::BeginMenu(MLX_UT_ICON_MD_HELP" Help"))
			{
				if(ImGui::MenuItem("About"))
					m_render_about_window = true;
				ImGui::EndMenu();
			}
			if(ImGui::Button("Launch All Tests"))
				m_launch_all_tests = true;
			ImGui::SameLine(static_cast<float>(size.x) * 0.5f - ImGui::CalcTextSize("MLX UnitTester").x * 0.5f);
			ImGui::TextUnformatted("MLX UnitTester");
			ImGui::SameLine(size.x - (ImGui::CalcTextSize("X").x * 3 + style->ItemSpacing.x * 3 + style->WindowPadding.x) * 2);
			if(ImGui::Button(MLX_UT_ICON_MD_REMOVE))
				SDL_MinimizeWindow(win.Get());
			bool maximized = (SDL_GetWindowFlags(win.Get()) & SDL_WINDOW_MAXIMIZED);
			if(ImGui::Button(maximized ? MLX_UT_ICON_MD_FULLSCREEN_EXIT : MLX_UT_ICON_MD_FULLSCREEN))
			{
				if(maximized)
					SDL_RestoreWindow(win.Get());
				else
					SDL_MaximizeWindow(win.Get());
			}
			if(ImGui::Button(MLX_UT_ICON_MD_CLOSE))
				m_quit_requested = true;
			m_height = ImGui::GetContentRegionAvail().y;
			ImGui::EndMainMenuBar();
		}

		if(m_launch_all_tests && m_mlx_lib_path.empty())
		{
			ImGui::OpenPopup("No mlx path");
			m_launch_all_tests = false;
		}

		ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
		ImGui::SetNextWindowSize(ImVec2(0, 80), ImGuiCond_Appearing);

		if(ImGui::BeginPopupModal("No mlx path", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
		{
			ImGui::Text("Cannot start testing, no mlx path given");
			if(ImGui::Button("Select mlx path", ImVec2(120, 0)))
			{
				m_dialog.Open("Select lib mlx", { "dynamic library (" MLX_UT_LIB_EXTENSION ")", "*" MLX_UT_LIB_EXTENSION });
				dialog_openned = true;
			}

			ImGui::SameLine();

			if(ImGui::Button("Continue", ImVec2(120, 0)))
				ImGui::CloseCurrentPopup();

			if(!m_mlx_lib_path.empty())
				ImGui::CloseCurrentPopup();
			ImGui::EndPopup();
		}

		#ifndef MLX_UT_EMBED_TESTS
			static char test_name[255] = { 0 };
			static bool error_no_name = false;
			if(new_test_openned)
				ImGui::OpenPopup("New test");
			ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
			ImGui::SetNextWindowSize(ImVec2(ImGui::CalcTextSize("Test name:  Your test needs a name !").x + 25, 0), ImGuiCond_Appearing);
			if(ImGui::BeginPopupModal("New test", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
			{
				std::string_view test_name_view{test_name};
				ImGui::TextUnformatted("Test name:");
				if(error_no_name)
				{
					ImGui::SameLine();
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.365f, 0.365f, 1.0f));
						ImGui::TextUnformatted("Your test needs a name !");
					ImGui::PopStyleColor();
				}
				ImGui::SetNextItemWidth(ImGui::GetWindowWidth() - ImGui::GetStyle().FramePadding.x * 2);
				if(ImGui::InputTextWithHint("##test_name", "Name", test_name, 255, ImGuiInputTextFlags_AutoSelectAll))
					error_no_name = false;

				ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() * 0.5f - ImGui::CalcTextSize("Create").x * 0.5f, ImGui::GetCursorPosY()));
				if(ImGui::Button("Create"))
				{
					if(!test_name_view.empty())
					{
						std::ofstream file(OSInstance::Get().GetCurrentWorkingDirectoryPath() / "Resources/Tests" / (std::string{ test_name_view } + ".lua"));
						if(file.is_open())
						{
							file << "function Setup(mlx, win)" << '\n';
							file << "end" << "\n\n";
							file << "function Test(mlx, win)" << '\n';
							file << "end" << "\n\n";
							file << "function Cleanup(mlx, win)" << '\n';
							file << "end";
						}
						file.close();
						tester.CreateAllTests(renderer);
						new_test_openned = false;
						std::memset(test_name, 0, 255);
						ImGui::CloseCurrentPopup();
					}
					else
						error_no_name = true;
				}

				ImGui::EndPopup();
			}
		#endif
	}

	void MenuBar::RenderMLXPath(const Renderer& renderer)
	{
		ImGui::SetNextWindowPos(ImVec2(0, renderer.GetDrawableSize().y - ImGui::GetFrameHeightWithSpacing()));
		if(m_mlx_lib_path.empty())
			ImGui::SetNextWindowSize(ImVec2(ImGui::CalcTextSize("MLX Path: None").x + 5, ImGui::GetFrameHeightWithSpacing()));
		else
			ImGui::SetNextWindowSize(ImVec2(ImGui::CalcTextSize(("MLX Path: " + m_mlx_lib_path.string()).c_str()).x + 5, ImGui::GetFrameHeightWithSpacing()));

		if(ImGui::Begin("##mlx_path", nullptr, ImGuiWindowFlags_NoDecoration))
		{
			ImGui::BringWindowToDisplayFront(ImGui::GetCurrentWindow());
			if(m_mlx_lib_path.empty())
				ImGui::TextUnformatted("MLX Path: None");
			else
				ImGui::TextUnformatted(("MLX Path: " + m_mlx_lib_path.string()).c_str());
			ImGui::End();
		}
	}

	void WebLink(const char* text, const char* url, ImVec2 pos)
	{
		ImGui::SetCursorPos(pos);
		ImGui::TextUnformatted(text);
		ImGui::SetCursorPos(pos);
		if(ImGui::InvisibleButton(text, ImGui::CalcTextSize(text)))
			OSInstance::Get().OpenURL(url);
		if(ImGui::IsItemHovered())
		{
			ImGui::SetCursorPos(pos);
			ImDrawList* draw_list = ImGui::GetForegroundDrawList();
			ImVec2 text_size = ImGui::CalcTextSize(text);
			ImVec2 abs_pos = ImGui::GetCursorScreenPos();
			ImVec4* colors = ImGui::GetStyle().Colors;
			draw_list->AddLine(ImVec2(abs_pos.x, abs_pos.y + text_size.y), ImVec2(abs_pos.x + text_size.x, abs_pos.y + text_size.y), ImGui::GetColorU32(ImGui::ColorConvertFloat4ToU32(colors[ImGuiCol_Text])));
			Application::Get().SetCursor(SDL_SYSTEM_CURSOR_HAND);
		}
	}

	void MenuBar::RenderAboutWindow()
	{
		if(ImGui::Begin(MLX_UT_ICON_MD_INFO" About", &m_render_about_window, ImGuiWindowFlags_NoMove |  ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_HorizontalScrollbar))
		{
			ImVec2 size = ImGui::GetWindowSize();
			ImGui::SetCursorPos(ImVec2(size.x / 7.0f, size.y / 7.0f));
			ImGui::Image(p_logo, ImVec2(size.x / 4.0f, size.x / 4.0f));

			#ifdef MLX_UT_DEBUG
				ImGui::SetCursorPos(ImVec2(size.x - ImGui::CalcTextSize("Debug version").x - 30.0f, size.y - ImGui::GetTextLineHeightWithSpacing() * 3.0f));
				ImGui::TextUnformatted("Debug version");
			#else
				ImGui::SetCursorPos(ImVec2(size.x - ImGui::CalcTextSize("Release version").x - 30, size.y - ImGui::GetTextLineHeightWithSpacing() * 3));
				ImGui::TextUnformatted("Release version");
			#endif
			ImGui::SetCursorPos(ImVec2(size.x / 2.0f, size.y / 3.0f));
			ImGui::TextWrapped(R"text(MacroLibX Unit Tester is a graphical unit tester for the MLX.
			)text");

			const std::string license_name = "License";
			const std::string mlx_name = "MacroLibX";
			const std::string sources_name = "Sources";

			WebLink(license_name.data(), "https://github.com/seekrs/MacroUnitTest/blob/master/LICENSE", ImVec2(size.x / 2.0f - ImGui::CalcTextSize(mlx_name.c_str()).x * 2.0f - ImGui::CalcTextSize(license_name.c_str()).x, size.y - size.y / 5.0f));
			WebLink(mlx_name.data(), "https://macrolibx.kbz8.me", ImVec2(size.x / 2.0f - ImGui::CalcTextSize(mlx_name.c_str()).x / 2.0f, size.y - size.y / 5.0f));
			WebLink(sources_name.data(), "https://github.com/seekrs/MacroUnitTest", ImVec2(size.x / 2.0f + ImGui::CalcTextSize(mlx_name.c_str()).x * 2.0f, size.y - size.y / 5.0f));

			ImGui::End();
		}
	}

	void MenuBar::RenderSettingsWindow()
	{
		if(ImGui::Begin(MLX_UT_ICON_MD_SETTINGS" Settings", &m_render_settings_window, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
		{
			static int selected = -1;
			if(ImGui::BeginChild("Setting selector", ImVec2{ 200.f, 0.f }, true))
			{
				if(ImGui::Selectable("General", selected == 0))
					selected = 0;
				ImGui::EndChild();
			}
			ImGui::SameLine(0);
			if(ImGui::BeginChild("Choices", ImVec2{ 0.f, 0.f }, true))
			{
				switch(selected)
				{
					case 0: RenderGeneralSettings(); break;

					default : break;
				}
				ImGui::EndChild();
			}
			ImGui::End();
		}
	}

	void MenuBar::DestroyResources()
	{
		if(p_logo != nullptr)
			SDL_DestroyTexture(p_logo);
	}

	void MenuBar::RenderGeneralSettings()
	{
		ImGui::TextUnformatted("General");
		ImGui::Separator();

		if(ImGui::BeginTable("general_settings_table", 2, ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH))
		{
			ImGui::TableSetupColumn("name", ImGuiTableColumnFlags_NoHeaderLabel | ImGuiTableColumnFlags_WidthFixed, ImGui::CalcTextSize("Global font scale").x + 10);
			ImGui::TableSetupColumn("value", ImGuiTableColumnFlags_NoHeaderLabel);

			ImGui::TableNextRow();
			ImGui::TableNextColumn();

			ImGui::TextUnformatted("Global theme");
			ImGui::TableNextColumn();
			{
				static std::size_t current_theme = 0;
				static std::array<std::pair<const char*, std::function<void(void)>>, 7> themes = {
					std::pair<const char*, std::function<void(void)>>{ "Dark", &ImGuiContext::SetDarkTheme },
					std::pair<const char*, std::function<void(void)>>{ "Light", &ImGuiContext::SetWhiteTheme },
					std::pair<const char*, std::function<void(void)>>{ "Dracula", &ImGuiContext::SetDraculaTheme },
					std::pair<const char*, std::function<void(void)>>{ "Cosy", &ImGuiContext::SetCosyTheme },
					std::pair<const char*, std::function<void(void)>>{ "Classic", [](){ ImGui::StyleColorsClassic(); } },
					std::pair<const char*, std::function<void(void)>>{ "Classic Dark", [](){ ImGui::StyleColorsDark(); } },
					std::pair<const char*, std::function<void(void)>>{ "Classic Light", [](){ ImGui::StyleColorsLight(); } },
				};
				if(ImGui::BeginCombo("##Theme_selector", themes[current_theme].first))
				{
					std::size_t i = 0;
					for(auto& [name, functor] : themes)
					{
						if(ImGui::Selectable(name, current_theme == i))
						{
							current_theme = i;
							functor();
						}
						i++;
					}
					ImGui::EndCombo();
				}
			}

			ImGui::TableNextRow();
			ImGui::TableNextColumn();

			ImGui::TextUnformatted("Global font scale");
			ImGui::TableNextColumn();
			{
				ImGuiIO& io = ImGui::GetIO();
				ImFont* current_font = ImGui::GetFont();
				static std::size_t current_size = 100;
				if(ImGui::BeginCombo("##Font_selector", (std::to_string(current_size) + "%").c_str()))
				{
					std::size_t size = 50;
					for(std::size_t i = 0; i < io.Fonts->Fonts.size() / 2; i++)
					{
						ImGui::PushID((void*)io.Fonts->Fonts[i]);
						if(ImGui::Selectable((std::to_string(size) + "%").c_str(), io.Fonts->Fonts[i] == current_font))
						{
							io.FontDefault = io.Fonts->Fonts[i];
							current_size = size;
						}
						ImGui::PopID();
						size += 25;
					}
					ImGui::EndCombo();
				}
			}

			ImGui::EndTable();
		}
	}
}

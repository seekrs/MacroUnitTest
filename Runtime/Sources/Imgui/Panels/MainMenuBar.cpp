#include <components/main_menu_bar.h>
#include <imgui.h>
#include <renderer.h>
#include <window.h>
#include <material_font.h>
#include <imspinner.h>
#include <tests/tester.h>

namespace mlxut
{
	MainMenuBar::MainMenuBar(const Renderer& renderer, Tester* tester) : _renderer(renderer), _tester(tester)
	{
		_logo = IMG_LoadTexture(renderer.getNativeRenderer(), "./resources/assets/logo.png");
	}

	void MainMenuBar::render(const Window& win, ivec2 size) noexcept
	{
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.f, 0.f, 0.f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0.f, 0.f, 0.f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.19f, 0.19f, 0.19f, 0.54f));

			if(!ImGui::BeginMainMenuBar())
				return;
			ImGui::Image(static_cast<void*>(_logo), ImVec2(20, 20));
			if(ImGui::Button("Launch all tests"))
				_tester->runAllTests();
			if(ImGui::BeginMenu("Help"))
			{
				if(ImGui::MenuItem("About"))
					_render_about_window = true;
				ImGui::EndMenu();
			}
			ImGui::SameLine(static_cast<float>(size.x) / 2.0f - ImGui::CalcTextSize("MacroLibX Unit Tester").x / 2.0f);
			ImGui::TextUnformatted("MacroLibX Unit Tester");
			ImGui::SameLine(size.x - 100);
			if(ImGui::Button(MLXUT_ICON_MD_REMOVE))
				SDL_MinimizeWindow(win.getNativeWindow());
			bool maximized = (SDL_GetWindowFlags(win.getNativeWindow()) & SDL_WINDOW_MAXIMIZED);
			if(ImGui::Button(maximized ? MLXUT_ICON_MD_FULLSCREEN_EXIT : MLXUT_ICON_MD_FULLSCREEN))
			{
				if(maximized)
					SDL_RestoreWindow(win.getNativeWindow());
				else
					SDL_MaximizeWindow(win.getNativeWindow());
			}
			if(ImGui::Button(MLXUT_ICON_MD_CLOSE))
				_quit_requested = true;
			ImGui::EndMainMenuBar();

		ImGui::PopStyleColor(4);

		if(_tester->testsAreRunning())
			ImGui::OpenPopup("Running All Tests");

		ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
		ImGui::SetNextWindowSize(ImVec2(ImGui::CalcTextSize("All the tests are running...").x + 50, 100), ImGuiCond_Appearing);
		if(ImGui::BeginPopupModal("Running All Tests", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
		{
			float windowWidth = ImGui::GetWindowWidth();
			float textWidth = ImGui::CalcTextSize("All the tests are running...").x;
			ImGui::SetCursorPosX((windowWidth - textWidth) / 2.0f);
			ImGui::TextUnformatted("All the tests are running...");

			const ImU32 bg = ImGui::GetColorU32(ImGuiCol_WindowBg);
			ImGui::SetCursorPosX((windowWidth - 45) / 2.0f);
			ImSpinner::SpinnerLoadingRing("##runningSpinner", 15, 3, ImSpinner::white, bg);

			if(!_tester->testsAreRunning())
				ImGui::CloseCurrentPopup();
			ImGui::EndPopup();
		}
	}

	void MainMenuBar::renderAboutWindow(ivec2 size)
	{
		if(!ImGui::Begin("About", &_render_about_window, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_HorizontalScrollbar))
			return;

		ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() / 2 - 128, ImGui::GetWindowHeight() / 8));
		ImGui::Image(static_cast<void*>(_logo), ImVec2(255, 255));

		ImGui::End();
	}

	void MainMenuBar::destroy() noexcept
	{
		if(_logo == nullptr)
			return;
		SDL_DestroyTexture(_logo);
		_logo = nullptr;
	}

	MainMenuBar::~MainMenuBar()
	{
		destroy();
	}
}

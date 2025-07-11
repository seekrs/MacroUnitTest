#include <Core/Application.h>
#include <Core/OS/OSInstance.h>
#include <Core/CLI.h>
#include <Core/EventBus.h>

#include <Graphics/Panels/Docks.h>
#include <Graphics/Panels/Logs.h>
#include <Graphics/Panels/Render.h>
#include <Graphics/Panels/Result.h>
#include <Graphics/Panels/Tests.h>
#include <Graphics/Panels/Script.h>

namespace mlxut
{
	Application::Application()
	{
		s_instance = this;

		std::function<void(const EventBase&)> functor = [](const EventBase& event)
		{
			if(event.What() == Event::FatalErrorEventCode)
				std::abort();
		};
		EventBus::RegisterListener({ functor, "Application" });

		if(!CommandLineInterface::Get().HasFlag("--headless"))
		{
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
			SDL_SetHintWithPriority(SDL_HINT_VIDEODRIVER, "wayland,x11", SDL_HINT_OVERRIDE);
		}
		else
			SDL_setenv("SDL_VIDEODRIVER", "dummy", 1);

		if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0)
			FatalError("SDL error: unable to init all subsystems, %", SDL_GetError());

		if(!CommandLineInterface::Get().HasFlag("--headless"))
		{
			LoadSystemCursors();
			p_window = std::make_unique<Window>("MLX UnitTester", MLX_UT_WINDOW_WIDTH, MLX_UT_WINDOW_HEIGHT);
			p_renderer = std::make_unique<Renderer>(*p_window);
			p_imgui = std::make_unique<ImGuiContext>(*p_window, *p_renderer);

			m_stack.AddPanel(std::make_shared<Docks>(m_menubar));
			m_stack.AddPanel(std::make_shared<LogsPanel>(m_tester));
			m_stack.AddPanel(std::make_shared<Render>(m_tester));
			m_stack.AddPanel(std::make_shared<ScriptPanel>(*p_renderer, m_tester));
			m_stack.AddPanel(std::make_shared<Results>(m_tester));
			m_stack.AddPanel(std::make_shared<TestsPanel>(m_tester));
		}
		m_tester.CreateAllTests(*p_renderer);
	}

	void Application::Run()
	{
		if(!CommandLineInterface::Get().HasFlag("--headless"))
		{
			for(;;)
			{
				m_wheel_event = MouseWheelEvent::Idle;

				while(SDL_PollEvent(&m_event))
				{
					if(m_event.type == SDL_QUIT)
						goto EndLoop;
					if(m_event.type == SDL_WINDOWEVENT && m_event.window.event == SDL_WINDOWEVENT_CLOSE)
						goto EndLoop;
					if(m_event.type == SDL_MOUSEWHEEL)
					{
						if(m_event.wheel.y > 0) // scroll up
							m_wheel_event = MouseWheelEvent::Up;
						else if(m_event.wheel.y < 0) // scroll down
							m_wheel_event = MouseWheelEvent::Down;
					}
					p_imgui->CheckEvents(&m_event);
				}
				UpdateCursor();

				Vec2i render_size = p_renderer->GetDrawableSize();
				ImVec2 im_render_size = ImVec2{ static_cast<float>(render_size.x), static_cast<float>(render_size.y) };

				p_imgui->BeginFrame();
					m_menubar.Render(*p_window, *p_renderer, im_render_size, m_tester);
					for(auto panel : m_stack.GetPanels())
						panel->OnUpdate(im_render_size);
					if(m_menubar.ShouldRenderSettingsWindow())
						m_menubar.RenderSettingsWindow();
					if(m_menubar.ShouldRenderAboutWindow())
						m_menubar.RenderAboutWindow();
					m_menubar.RenderMLXPath(*p_renderer);

					if(m_have_tests_been_launched)
						ImGui::OpenPopup("Running");

					ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
					ImGui::SetNextWindowSize(ImVec2(ImGui::CalcTextSize("Tests are currently running").x + 50, 100), ImGuiCond_Appearing);
					if(ImGui::BeginPopupModal("Running", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
					{
						float window_width = ImGui::GetWindowWidth();
						float text_width = ImGui::CalcTextSize("Tests are currently running").x;
						ImGui::SetCursorPosX((window_width - text_width) / 2.0f);
						ImGui::Text("Tests are currently running");

						const ImU32 bg = ImGui::GetColorU32(ImGuiCol_WindowBg);
						ImGui::SetCursorPosX((window_width - 45) / 2.0f);
						ImSpinner::SpinnerLoadingRing("##running_spinner", 15, 3, ImSpinner::white, bg);

						if(!m_have_tests_been_launched)
							ImGui::CloseCurrentPopup();

						ImGui::EndPopup();
					}
				p_imgui->EndFrame();

				if(m_have_tests_been_launched && m_tester.HaveAllTestsFinished())
				{
					m_tester.FetchAllResults();
					m_tester.CreateAllRenderTextures();
					m_tester.ComputeAllErrorMaps();
					m_tester.FetchSuccess();
					m_have_tests_been_launched = false;
				}

				if(m_menubar.ShouldStartAllTests())
					m_tester.RunAllTests(m_menubar.GetMLXPath());

				if(m_menubar.IsQuitRequested())
					break;
			}

		EndLoop:
			m_menubar.DestroyResources();
			return;
		}
	}

	Application::~Application()
	{
		if(!CommandLineInterface::Get().HasFlag("--headless"))
		{
			m_stack.Destroy();

			p_imgui.reset();
			p_renderer.reset();
			p_window.reset();

			SDL_QuitSubSystem(SDL_INIT_VIDEO);
			SDL_QuitSubSystem(SDL_INIT_TIMER);
			SDL_QuitSubSystem(SDL_INIT_EVENTS);
			SDL_Quit();
		}

		s_instance = nullptr;
	}

	void Application::LoadSystemCursors() noexcept
	{
		m_cursors[SDL_SYSTEM_CURSOR_ARROW] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
		m_cursors[SDL_SYSTEM_CURSOR_IBEAM] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
		m_cursors[SDL_SYSTEM_CURSOR_WAIT] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAIT);
		m_cursors[SDL_SYSTEM_CURSOR_CROSSHAIR] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
		m_cursors[SDL_SYSTEM_CURSOR_WAITARROW] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAITARROW);
		m_cursors[SDL_SYSTEM_CURSOR_SIZENWSE] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENWSE);
		m_cursors[SDL_SYSTEM_CURSOR_SIZENESW] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENESW);
		m_cursors[SDL_SYSTEM_CURSOR_SIZEWE] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
		m_cursors[SDL_SYSTEM_CURSOR_SIZENS] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
		m_cursors[SDL_SYSTEM_CURSOR_SIZEALL] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
		m_cursors[SDL_SYSTEM_CURSOR_NO] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NO);
		m_cursors[SDL_SYSTEM_CURSOR_HAND] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}

	void Application::UpdateCursor() noexcept
	{
		int w, h;
		SDL_GetWindowSize(p_window->Get(), &w, &h);
		int x, y;
		SDL_GetMouseState(&x, &y);
		if(y < RESIZE_MARGIN && x > 275 && x < w - 95)
		{
			if(x < RESIZE_MARGIN)
				SDL_SetCursor(m_cursors[SDL_SYSTEM_CURSOR_SIZENWSE]);
			else if(x > w - RESIZE_MARGIN)
				SDL_SetCursor(m_cursors[SDL_SYSTEM_CURSOR_SIZENESW]);
			else
				SDL_SetCursor(m_cursors[SDL_SYSTEM_CURSOR_SIZENS]);
		}
		else if(y > h - RESIZE_MARGIN)
		{
			if(x < RESIZE_MARGIN)
				SDL_SetCursor(m_cursors[SDL_SYSTEM_CURSOR_SIZENESW]);
			else if(x > w - RESIZE_MARGIN)
				SDL_SetCursor(m_cursors[SDL_SYSTEM_CURSOR_SIZENWSE]);
			else
				SDL_SetCursor(m_cursors[SDL_SYSTEM_CURSOR_SIZENS]);
		}
		else if(x < RESIZE_MARGIN)
			SDL_SetCursor(m_cursors[SDL_SYSTEM_CURSOR_SIZEWE]);
		else if(x > w - RESIZE_MARGIN)
			SDL_SetCursor(m_cursors[SDL_SYSTEM_CURSOR_SIZEWE]);
		else
			SDL_SetCursor(m_cursors[SDL_SYSTEM_CURSOR_ARROW]);
	}
}

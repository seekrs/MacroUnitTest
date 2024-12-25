#include <Graphics/ImGuiContext.h>
#include <Core/MaterialFont.h>
#include <Core/OS/OSInstance.h>

#ifdef MLX_UT_RELEASE
	#include <Embedded/Fonts.h>
#endif

namespace mlxut
{
	ImGuiContext::ImGuiContext(const class Window& win, const class Renderer& renderer) : m_renderer(renderer)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.IniFilename = nullptr;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		SetDarkTheme();

		ImGui_ImplSDL2_InitForSDLRenderer(win.Get(), renderer.Get());
		ImGui_ImplSDLRenderer2_Init(renderer.Get());

		io.Fonts->ClearFonts();
		static const ImWchar icons_ranges[] = { MLX_UT_ICON_MIN_MD, MLX_UT_ICON_MAX_16_MD, 0 };
		static ImFontConfig config;
		config.MergeMode = true;
		config.GlyphOffset.y = 4.0f;
		config.GlyphRanges = icons_ranges;

		for(std::size_t size = 14; size < 32; size += 2)
		{
			#ifndef MLX_UT_RELEASE
				ImFont* font = io.Fonts->AddFontFromFileTTF((OSInstance::Get().GetCurrentWorkingDirectoryPath() / "Resources/Fonts/OpenSans/OpenSans_Regular.ttf").string().c_str(), static_cast<float>(size));
				ImFont* icon_font = io.Fonts->AddFontFromFileTTF((OSInstance::Get().GetCurrentWorkingDirectoryPath() / "Resources/Fonts/MaterialIcons_Regular.ttf").string().c_str(), static_cast<float>(size), &config, icons_ranges);
			#else
				ImFont* font = io.Fonts->AddFontFromMemoryTTF(reinterpret_cast<void*>(const_cast<std::uint8_t*>(OpenSans_Regular_data.data())), OpenSans_Regular_data.size(), static_cast<float>(size));
				ImFont* icon_font = io.Fonts->AddFontFromMemoryTTF(reinterpret_cast<void*>(const_cast<std::uint8_t*>(MaterialIcons_Regular_data.data())), MaterialIcons_Regular_data.size(), static_cast<float>(size), &config, icons_ranges);
			#endif
			Verify(font != nullptr, "could not load open sans font");
			Verify(icon_font != nullptr, "could not load material font");
			if(size == 18)
				io.FontDefault = font;
		}
	}

	void ImGuiContext::CheckEvents(const SDL_Event* event) noexcept
	{
		ImGui_ImplSDL2_ProcessEvent(event);
	}

	void ImGuiContext::BeginFrame() noexcept
	{
		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiContext::EndFrame() noexcept
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGui::Render();
		SDL_RenderSetScale(m_renderer.Get(), io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
		SDL_SetRenderDrawColor(m_renderer.Get(), 0, 0, 0, 255);
		SDL_RenderClear(m_renderer.Get());
		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), m_renderer.Get());
		SDL_RenderPresent(m_renderer.Get());
	}

	ImGuiContext::~ImGuiContext()
	{
		ImGui_ImplSDLRenderer2_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiContext::SetDarkTheme()
	{
		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4* colors = style->Colors;

		ImGui::StyleColorsDark();
		colors[ImGuiCol_Text]                  = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled]          = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg]              = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		colors[ImGuiCol_ChildBg]               = ImVec4(0.20f, 0.20f, 0.20f, 0.20f);
		colors[ImGuiCol_PopupBg]               = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
		colors[ImGuiCol_Border]                = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
		colors[ImGuiCol_FrameBg]               = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
		colors[ImGuiCol_FrameBgActive]         = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		colors[ImGuiCol_TitleBg]               = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_TitleBgActive]         = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_MenuBarBg]             = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
		colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
		colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
		colors[ImGuiCol_CheckMark]             = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
		colors[ImGuiCol_SliderGrab]            = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
		colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
		colors[ImGuiCol_Button]                = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_ButtonHovered]         = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
		colors[ImGuiCol_ButtonActive]          = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		colors[ImGuiCol_Header]                = ImVec4(0.05f, 0.05f, 0.05f, 0.52f);
		colors[ImGuiCol_HeaderHovered]         = ImVec4(0.05f, 0.05f, 0.05f, 0.36f);
		colors[ImGuiCol_HeaderActive]          = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
		colors[ImGuiCol_Separator]             = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
		colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
		colors[ImGuiCol_SeparatorActive]       = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
		colors[ImGuiCol_ResizeGrip]            = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
		colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
		colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
		colors[ImGuiCol_Tab]                   = ImVec4(0.05f, 0.05f, 0.05f, 0.52f);
		colors[ImGuiCol_TabHovered]            = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_TabActive]             = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		colors[ImGuiCol_TabUnfocused]          = ImVec4(0.05f, 0.05f, 0.05f, 0.52f);
		colors[ImGuiCol_TabUnfocusedActive]    = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		colors[ImGuiCol_DockingPreview]        = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
		colors[ImGuiCol_DockingEmptyBg]        = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotLines]             = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogram]         = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_TableHeaderBg]         = ImVec4(0.05f, 0.05f, 0.05f, 0.52f);
		colors[ImGuiCol_TableBorderStrong]     = ImVec4(0.05f, 0.05f, 0.05f, 0.52f);
		colors[ImGuiCol_TableBorderLight]      = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
		colors[ImGuiCol_TableRowBg]            = ImVec4(0.05f, 0.05f, 0.05f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt]         = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		colors[ImGuiCol_DragDropTarget]        = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
		colors[ImGuiCol_NavHighlight]          = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

		style->ChildRounding = 4.0f;
		style->FrameBorderSize = 1.0f;
		style->FrameRounding = 2.0f;
		style->GrabMinSize = 7.0f;
		style->PopupRounding = 2.0f;
		style->ScrollbarRounding = 12.0f;
		style->ScrollbarSize = 13.0f;
		style->TabBorderSize = 0.0f;
		style->TabRounding = 5.0f;
		style->WindowPadding = ImVec2(3.f, 3.f);
		style->WindowRounding = 0.0f;
		style->WindowBorderSize = 1.0f;
		style->AntiAliasedLines = true;
		style->AntiAliasedFill = true;
		style->TabBorderSize = 2.0f;
	}

	void ImGuiContext::SetWhiteTheme()
	{
		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4* colors = style->Colors;

		ImGui::StyleColorsLight();
		colors[ImGuiCol_Text]                 = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_TextDisabled]         = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
		colors[ImGuiCol_WindowBg]             = ImVec4(0.94f, 0.94f, 0.94f, 0.94f);
		colors[ImGuiCol_PopupBg]              = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
		colors[ImGuiCol_Border]               = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
		colors[ImGuiCol_BorderShadow]         = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
		colors[ImGuiCol_FrameBg]              = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
		colors[ImGuiCol_FrameBgHovered]       = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
		colors[ImGuiCol_FrameBgActive]        = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_TitleBg]              = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed]     = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
		colors[ImGuiCol_TitleBgActive]        = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
		colors[ImGuiCol_MenuBarBg]            = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
		colors[ImGuiCol_ScrollbarBg]          = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab]        = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive]  = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
		colors[ImGuiCol_CheckMark]            = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_SliderGrab]           = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
		colors[ImGuiCol_SliderGrabActive]     = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_Button]               = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
		colors[ImGuiCol_ButtonHovered]        = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_ButtonActive]         = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
		colors[ImGuiCol_Header]               = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
		colors[ImGuiCol_HeaderHovered]        = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
		colors[ImGuiCol_HeaderActive]         = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_ResizeGrip]           = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
		colors[ImGuiCol_ResizeGripHovered]    = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_ResizeGripActive]     = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		colors[ImGuiCol_PlotLines]            = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered]     = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram]        = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg]       = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);

		style->ChildRounding = 4.0f;
		style->FrameBorderSize = 1.0f;
		style->FrameRounding = 2.0f;
		style->GrabMinSize = 7.0f;
		style->PopupRounding = 2.0f;
		style->ScrollbarRounding = 12.0f;
		style->ScrollbarSize = 13.0f;
		style->TabBorderSize = 0.0f;
		style->TabRounding = 5.0f;
		style->WindowPadding = ImVec2(3.f, 3.f);
		style->WindowRounding = 0.0f;
		style->WindowBorderSize = 1.0f;
		style->AntiAliasedLines = true;
		style->AntiAliasedFill = true;
		style->TabBorderSize = 2.0f;
	}

	void ImGuiContext::SetDraculaTheme()
	{
		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4* colors = style->Colors;
		const float max = 255.0f;

		ImGui::StyleColorsDark();

		ImVec4 Titlebar    = ImVec4(33.0f / max, 34.0f / max, 44.0f / max, 1.0f);
		ImVec4 TabActive   = ImVec4(40.0f / max, 42.0f / max, 54.0f / max, 1.0f);
		ImVec4 TabUnactive = ImVec4(35.0f / max, 43.0f / max, 59.0f / max, 1.0f);

		colors[ImGuiCol_Text]                  = ImVec4(244.0f / 255.0f, 244.0f / 255.0f, 244.0f / 255.0f, 1.00f);
		colors[ImGuiCol_TextDisabled]          = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
		colors[ImGuiCol_WindowBg]              = TabActive;
		colors[ImGuiCol_ChildBg]               = TabActive;
		colors[ImGuiCol_PopupBg]               = ImVec4(42.0f / 255.0f, 38.0f / 255.0f, 47.0f / 255.0f, 1.00f);
		colors[ImGuiCol_Border]                = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
		colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg]               = ImVec4(65.0f / 255.0f, 79.0f / 255.0f, 92.0f / 255.0f, 1.00f);
		colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
		colors[ImGuiCol_FrameBgActive]         = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
		colors[ImGuiCol_TitleBg]               = Titlebar;
		colors[ImGuiCol_TitleBgActive]         = Titlebar;
		colors[ImGuiCol_TitleBgCollapsed]      = Titlebar;
		colors[ImGuiCol_MenuBarBg]             = Titlebar;
		colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
		colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.6f, 0.6f, 0.6f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.7f, 0.7f, 0.7f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.8f, 0.8f, 0.8f, 1.00f);
		colors[ImGuiCol_CheckMark]             = ImVec4(155.0f / 255.0f, 130.0f / 255.0f, 207.0f / 255.0f, 1.00f);
		colors[ImGuiCol_SliderGrab]            = ImVec4(155.0f / 255.0f, 130.0f / 255.0f, 207.0f / 255.0f, 1.00f);
		colors[ImGuiCol_SliderGrabActive]      = ImVec4(185.0f / 255.0f, 160.0f / 255.0f, 237.0f / 255.0f, 1.00f);
		colors[ImGuiCol_Button]                = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
		colors[ImGuiCol_ButtonHovered]         = ImVec4(59.0f / 255.0f, 46.0f / 255.0f, 80.0f / 255.0f, 1.0f);
		colors[ImGuiCol_ButtonActive]          = ImVec4(59.0f / 255.0f + 0.1f, 46.0f / 255.0f + 0.1f, 80.0f / 255.0f + 0.1f, 1.0f);
		colors[ImGuiCol_Separator]             = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
		colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
		colors[ImGuiCol_SeparatorActive]       = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
		colors[ImGuiCol_ResizeGrip]            = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
		colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		colors[ImGuiCol_PlotLines]             = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		colors[ImGuiCol_DragDropTarget]        = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavHighlight]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		colors[ImGuiCol_Header]                = TabActive;
		colors[ImGuiCol_HeaderHovered]         = TabActive;
		colors[ImGuiCol_HeaderActive]          = TabActive;

		style->ChildRounding = 4.0f;
		style->FrameBorderSize = 1.0f;
		style->FrameRounding = 2.0f;
		style->GrabMinSize = 7.0f;
		style->PopupRounding = 2.0f;
		style->ScrollbarRounding = 12.0f;
		style->ScrollbarSize = 13.0f;
		style->TabBorderSize = 0.0f;
		style->TabRounding = 5.0f;
		style->WindowPadding = ImVec2(3.f, 3.f);
		style->WindowRounding = 0.0f;
		style->WindowBorderSize = 1.0f;
		style->AntiAliasedLines = true;
		style->AntiAliasedFill = true;
		style->TabBorderSize = 2.0f;
	}

	void ImGuiContext::SetCosyTheme()
	{
		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4* colors = style->Colors;
		const float max = 255.0f;

		ImVec4 background             = ImVec4(39.0f / 255.0f, 40.0f / 255.0f, 47.0f / 255.0f, 255.0f / 255.0f);
		ImVec4 foreground             = ImVec4(42.0f / 255.0f, 44.0f / 255.0f, 54.0f / 255.0f, 255.0f / 255.0f);
		ImVec4 text                   = ImVec4(230.0f / 255.0f, 175.0f / 255.0f, 137.0f / 255.0f, 255.0f / 255.0f);
		ImVec4 text_secondary         = ImVec4(159.0f / 255.0f, 159.0f / 255.0f, 176.0f / 255.0f, 255.0f / 255.0f);
		ImVec4 text_background        = ImVec4(97.0f / 255.0f, 97.0f / 255.0f, 106.0f / 255.0f, 255.0f / 255.0f);
		ImVec4 text_blue              = ImVec4(110.0f / 255.0f, 150.0f / 255.0f, 200.0f / 255.0f, 255.0f / 255.0f);
		ImVec4 text_orange            = ImVec4(183.0f / 255.0f, 113.0f / 255.0f, 96.0f / 255.0f, 255.0f / 255.0f);
		ImVec4 text_yellow            = ImVec4(214.0f / 255.0f, 199.0f / 255.0f, 130.0f / 255.0f, 255.0f / 255.0f);
		ImVec4 text_red               = ImVec4(206.0f / 255.0f, 120.0f / 255.0f, 105.0f / 255.0f, 255.0f / 255.0f);
		ImVec4 highlight_primary      = ImVec4(47.0f / 255.0f, 179.0f / 255.0f, 135.0f / 255.0f, 255.0f / 255.0f);
		ImVec4 hover_primary          = ImVec4(76.0f / 255.0f, 148.0f / 255.0f, 123.0f / 255.0f, 255.0f / 255.0f);
		ImVec4 highlight_secondary    = ImVec4(76.0f / 255.0f, 48.0f / 255.0f, 67.0f / 255.0f, 255.0f / 255.0f);
		ImVec4 hover_secondary        = ImVec4(105.0f / 255.0f, 50.0f / 255.0f, 68.0f / 255.0f, 255.0f / 255.0f);
		ImVec4 checkerboard_primary   = ImVec4(150.0f / 255.0f, 150.0f / 255.0f, 150.0f / 255.0f, 255.0f / 255.0f);
		ImVec4 checkerboard_secondary = ImVec4(100.0f / 255.0f, 100.0f / 255.0f, 100.0f / 255.0f, 255.0f / 255.0f);
		ImVec4 modal_dim              = ImVec4(0, 0, 0, 48.0f / 255.0f);

		ImGui::StyleColorsDark();
		colors[ImGuiCol_Text]           = text;
		colors[ImGuiCol_TextDisabled]   = text_background;
		colors[ImGuiCol_TextSelectedBg] = text_secondary;

		colors[ImGuiCol_WindowBg] = background;
		colors[ImGuiCol_ChildBg]  = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg]  = background;

		colors[ImGuiCol_Border]         = foreground;
		colors[ImGuiCol_BorderShadow]   = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
		colors[ImGuiCol_FrameBg]        = foreground;
		colors[ImGuiCol_FrameBgHovered] = foreground;
		colors[ImGuiCol_FrameBgActive]  = foreground;

		colors[ImGuiCol_TitleBg]          = foreground;
		colors[ImGuiCol_TitleBgActive]    = foreground;
		colors[ImGuiCol_TitleBgCollapsed] = foreground;
		colors[ImGuiCol_MenuBarBg]        = foreground;

		colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
		colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
		colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
		colors[ImGuiCol_CheckMark]             = checkerboard_primary;
		colors[ImGuiCol_SliderGrab]            = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
		colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
		colors[ImGuiCol_Button]                = foreground;
		colors[ImGuiCol_ButtonHovered]         = hover_secondary;
		colors[ImGuiCol_ButtonActive]          = highlight_secondary;
		colors[ImGuiCol_Header]                = highlight_secondary;
		colors[ImGuiCol_HeaderHovered]         = highlight_secondary;
		colors[ImGuiCol_HeaderActive]          = highlight_secondary;
		colors[ImGuiCol_Separator]             = foreground;
		colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
		colors[ImGuiCol_SeparatorActive]       = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
		colors[ImGuiCol_ResizeGrip]            = highlight_primary;
		colors[ImGuiCol_ResizeGripHovered]     = highlight_secondary;
		colors[ImGuiCol_ResizeGripActive]      = highlight_secondary;
		colors[ImGuiCol_Tab]                   = background;
		colors[ImGuiCol_TabHovered]            = foreground;
		colors[ImGuiCol_TabActive]             = foreground;
		colors[ImGuiCol_TabUnfocused]          = background;
		colors[ImGuiCol_TabUnfocusedActive]    = foreground;
		colors[ImGuiCol_DockingPreview]        = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
		colors[ImGuiCol_DockingEmptyBg]        = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotLines]             = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogram]         = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_TableHeaderBg]         = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TableBorderStrong]     = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TableBorderLight]      = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
		colors[ImGuiCol_DragDropTarget]        = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
		colors[ImGuiCol_NavHighlight]          = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		colors[ImGuiCol_ModalWindowDimBg]      = modal_dim;

		style->ChildRounding = 4.0f;
		style->FrameBorderSize = 1.0f;
		style->FrameRounding = 2.0f;
		style->GrabMinSize = 7.0f;
		style->PopupRounding = 2.0f;
		style->ScrollbarRounding = 12.0f;
		style->ScrollbarSize = 13.0f;
		style->TabBorderSize = 0.0f;
		style->TabRounding = 5.0f;
		style->WindowPadding = ImVec2(3.f, 3.f);
		style->WindowRounding = 0.0f;
		style->WindowBorderSize = 1.0f;
		style->AntiAliasedLines = true;
		style->AntiAliasedFill = true;
		style->TabBorderSize = 2.0f;
	}
}

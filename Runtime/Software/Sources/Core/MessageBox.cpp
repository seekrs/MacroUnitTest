#include <Core/MessageBox.h>

namespace mlxut
{
	void MessageBox(std::string_view message, LogType type)
	{
		std::string title;
		std::uint32_t flag;

		switch(type)
		{
			case LogType::Message : flag = SDL_MESSAGEBOX_INFORMATION; title = "MLX Tester Message"; break;
			case LogType::Warning : flag = SDL_MESSAGEBOX_WARNING; title = "MLX Tester Error"; break;
			case LogType::Error : flag = SDL_MESSAGEBOX_ERROR; title = "MLX Tester Warning"; break;
			case LogType::FatalError : flag = SDL_MESSAGEBOX_ERROR; title = "MLX Tester Error"; break;

			default: return;
		}

		SDL_MessageBoxButtonData button = { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Ok" };
		const SDL_MessageBoxColorScheme color_scheme = {{
				{ 56, 54, 53 },
				{ 233, 233, 233 },
				{ 180, 180, 180 },
				{ 105, 102, 99 },
				{ 160, 160, 160 }
		}};
		SDL_MessageBoxData messageboxdata = { flag, nullptr, title.data(), message.data(), 1, &button, &color_scheme };
		int buttonid;
		SDL_ShowMessageBox(&messageboxdata, &buttonid);
	}
}

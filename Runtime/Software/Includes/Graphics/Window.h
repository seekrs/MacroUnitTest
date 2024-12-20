#ifndef MLX_UT_WINDOW
#define MLX_UT_WINDOW

#include <PreCompiled.h>

namespace mlxut
{
	class Window
	{
		public:
			Window(std::string title, std::size_t w, std::size_t h);

			[[nodiscard]] inline SDL_Window* const Get() const noexcept { return p_window; }

			~Window();

		private:
			SDL_Window* p_window = nullptr;
			SDL_Surface* p_icon = nullptr;
	};
}

#endif

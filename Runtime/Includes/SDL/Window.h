#ifndef MLX_UT_WINDOW
#define MLX_UT_WINDOW

#include <Pch.h>

namespace mlxut
{
	class Window
	{
		public:
			Window(std::string title, std::size_t w, std::size_t h);

			inline SDL_Window* const Get() const noexcept { return p_win; }
			void Destroy() noexcept;

			~Window();

		private:
			SDL_Window* p_win;
			SDL_Surface* p_icon;
	};
}

#endif

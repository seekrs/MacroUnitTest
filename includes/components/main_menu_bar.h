/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu_bar.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:41:43 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/20 13:55:56 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_MAIN_MENU_BAR__
#define __MLX_UT_MAIN_MENU_BAR__

#include <pch.h>

namespace mlxut
{
	class MainMenuBar
	{
		public:
			MainMenuBar(const class Renderer& renderer);
			void render(const class Window& win, ivec2 size) noexcept;
			void renderAboutWindow(ivec2 size);
			inline bool shouldRenderAboutWindow() const noexcept { return _render_about_window; }
			inline bool quitRequested() const noexcept { return _quit_requested; }
			void destroy() noexcept;
			~MainMenuBar();

		private:
			SDL_Texture* _logo = nullptr;
			bool _render_about_window = false;
			bool _quit_requested = false;
	};
}

#endif

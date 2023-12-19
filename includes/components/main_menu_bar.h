/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu_bar.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:41:43 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/19 21:52:03 by maldavid         ###   ########.fr       */
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
			MainMenuBar() = default;
			void render(ivec2 size) noexcept;
			~MainMenuBar() = default;

		private:
			void renderAboutWindow(ivec2 size);

		private:
			bool _render_about_window = false;
	};
}

#endif

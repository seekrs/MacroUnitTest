/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:37:01 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/19 17:15:09 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_WINDOW__
#define __MLX_UT_WINDOW__

#include <pch.h>

namespace mlxut
{
	class Window
	{
		public:
			Window(const std::string& title, std::size_t w, std::size_t h);
			inline SDL_Window* const getNativeWindow() const noexcept { return _win; }
			void destroy() noexcept;
			~Window();

		private:
			SDL_Window* _win = nullptr;
			SDL_Surface* _icon = nullptr;
	};
}

#endif

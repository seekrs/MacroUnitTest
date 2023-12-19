/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:57:16 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/19 17:15:03 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_RENDERER__
#define __MLX_UT_RENDERER__

#include <pch.h>

namespace mlxut
{
	class Renderer
	{
		public:
			Renderer(const class Window& win);
			inline SDL_Renderer* const getNativeRenderer() const noexcept { return _renderer; }
			void destroy() noexcept;
			~Renderer();

		private:
			SDL_Renderer* _renderer = nullptr;
	};
}

#endif

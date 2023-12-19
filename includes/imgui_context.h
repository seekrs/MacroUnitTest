/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgui_context.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:05:15 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/19 17:35:45 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_IMGUI_CONTEXT__
#define __MLX_UT_IMGUI_CONTEXT__

namespace mlxut
{
	class ImGuiContext
	{
		public:
			ImGuiContext(const class Window& win, const class Renderer& renderer);
			bool checkEvents() noexcept;
			void beginFrame() noexcept;
			void endFrame() noexcept;
			void destroy() noexcept;
			~ImGuiContext();

		private:
			void setDarkTheme();

		private:
			const class Renderer& _renderer;
			bool _is_init = false;
	};
}

#endif

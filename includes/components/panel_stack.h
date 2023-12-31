/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel_stack.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:14:22 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/19 23:53:05 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_PANEL_STACK__
#define __MLX_UT_PANEL_STACK__

#include <pch.h>
#include <components/panel.h>

namespace mlxut
{
	class PanelStack
	{
		public:
			PanelStack() = default;

			void addPanel(Panel* const panel);

			void removePanel(Panel* const panel);
			void removePanel(const std::string& name);

			Panel* const getPanel(const std::string& name);
			Panel* const getPanel(std::size_t index);

			inline const std::vector<Panel*>& getPanels() const { return _panels; }

			~PanelStack() = default;

		private:
			std::vector<Panel*> _panels;
	};
}

#endif

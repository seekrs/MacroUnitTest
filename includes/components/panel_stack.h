/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel_stack.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:14:22 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/19 18:24:00 by maldavid         ###   ########.fr       */
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

			inline std::vector<Panel*>::iterator begin() { return _panels.begin(); }
			inline std::vector<Panel*>::iterator end() { return _panels.end(); }
			inline std::vector<Panel*>::reverse_iterator rbegin() { return _panels.rbegin(); }
			inline std::vector<Panel*>::reverse_iterator rend() { return _panels.rend(); }

			inline std::vector<Panel*>::const_iterator cbegin() { return _panels.cbegin(); }
			inline std::vector<Panel*>::const_iterator cend() { return _panels.cend(); }
			inline std::vector<Panel*>::const_reverse_iterator crbegin() { return _panels.crbegin(); }
			inline std::vector<Panel*>::const_reverse_iterator crend() { return _panels.crend(); }

			~PanelStack() = default;

		private:
			std::vector<Panel*> _panels;
	};
}

#endif

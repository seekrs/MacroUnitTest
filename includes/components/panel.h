/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:42:33 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/19 17:48:10 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pch.h>

namespace mlxut
{
	class Panel
	{
		public:
			Panel(const std::string& name);

			virtual void onAttach() {}
			virtual void onOpen() {}
			virtual bool isOpen() {}
			virtual void onUpdate([[maybe_unused]] ImVec2 size) {}
			virtual void onQuit() {}

			inline const std::string& getName() const noexcept { return _name }
			inline void setName(const std::string& name) noexcept { _name = name; }
			virtual ~Panel();

		protected:
			std::string _name;
			ImVec2 _size;
			
	};
}

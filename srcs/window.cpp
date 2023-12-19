/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:36:51 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/19 15:56:01 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <window.h>

namespace mlxut
{
	Window::Window(const std::string& title, std::size_t w, std::size_t h)
	{

	}

	void Window::destroy() noecxept
	{
		
	}

	Window::~Window()
	{
		destroy();
	}
}

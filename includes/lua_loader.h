/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lua_loader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 22:32:27 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/27 23:03:42 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LUA_LOADER__
#define __LUA_LOADER__

#include <pch.h>
#include <lua_script.h>

namespace mlxut
{
	class LuaLoader
	{
		public:
			LuaLoader();
			std::optional<LuaScript> loadScript(const std::filesystem::path& path);
			~LuaLoader() = default;

		private:
			sol::state _state;
	};
}

#endif

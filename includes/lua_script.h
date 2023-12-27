/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lua_script.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 22:35:51 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/27 23:54:56 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LUA_SCRIPT__
#define __LUA_SCRIPT__

#include <pch.h>

namespace mlxut
{
	class LuaScript
	{
		friend class LuaLoader;

		public:
			LuaScript() = default;

			void runOnSetup(void* mlx, void* win);
			void runOnUpdate(void* mlx, void* win);
			void runOnQuit(void* mlx, void* win);

			inline bool failed() const noexcept { return _failed; }

			~LuaScript() = default;

		private:
			sol::environment _env;
			sol::protected_function _on_setup;
			sol::protected_function _on_update;
			sol::protected_function _on_quit;
			bool _failed = false;
	};
}

#endif

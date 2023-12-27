/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_test.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:15:26 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/27 23:56:27 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_TEST__
#define __MLX_UT_TEST__

#include <pch.h>
#include <loader/loader.h>
#include <renderer.h>
#include <lua_script.h>

namespace mlxut
{
	class Test
	{
		friend class Tester;

		public:
			enum class state
			{
				pending,
				success,
				fail
			};

		public:
			Test(const Renderer& renderer, const LuaScript& script, const std::string& name) : _script(script), _name(name)
			{
				std::filesystem::path ref_path("resources/assets/tests_references");
				ref_path /= name + ".png";
				if(!std::filesystem::exists(ref_path))
					return;
				_reference = IMG_LoadTexture(renderer.getNativeRenderer(), ref_path.string().c_str());
			}

			inline void setRenderData(void* mlx, void* win) noexcept { _mlx = mlx; _win = win;}
			inline void setMLXinfos(const std::string& mlx_infos) { _mlx_infos = mlx_infos; }
			inline void destroyResult() noexcept { SDL_DestroyTexture(_result); _result = nullptr; }
			inline void setResultTexture(SDL_Texture* result) noexcept { _result = result; }

			inline constexpr void failed() noexcept { _state = state::fail; } 
			inline constexpr void succeeded() noexcept { _state = state::success; } 

			inline SDL_Texture* getResult() const noexcept { return _result; }
			inline SDL_Texture* getReference() const noexcept { return _reference; }
			
			inline const std::string& getName() const noexcept { return _name; }
			inline const std::string& getMLXinfos() const noexcept { return _mlx_infos; }

			inline bool hasPassed() const noexcept { return _state == state::success; }
			inline bool hasFailed() const noexcept { return _state == state::fail; }
			inline bool isPending() const noexcept { return _state == state::pending; }

			inline void onSetup(void* mlx, void* win) noexcept { _script.runOnSetup(mlx, win); }
			inline void onUpdate(void* mlx, void* win) noexcept { _script.runOnUpdate(mlx, win); }
			inline void onQuit(void* mlx, void* win) noexcept { _script.runOnQuit(mlx, win); }

			inline bool hasScriptFailed() const noexcept { return _script.failed(); }

			~Test() { destroyResult(); SDL_DestroyTexture(_reference); }

		protected:
			LuaScript _script;
			std::string _name;
			SDL_Texture* _reference = nullptr;
			SDL_Texture* _result = nullptr;
			void* _mlx = nullptr;
			void* _win = nullptr;
			std::string _mlx_infos;
			state _state = state::pending;
	};
}

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_test.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:15:26 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/25 15:15:46 by kbz_8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_BASE_TEST__
#define __MLX_UT_BASE_TEST__

#include <pch.h>
#include <loader/loader.h>
#include <renderer.h>

namespace mlxut
{
	class BaseTest
	{
		friend class Tester;

		public:
			BaseTest(const Renderer& renderer, const std::string& name) : _name(name)
			{
				std::filesystem::path ref_path("resources/assets/tests_references");
				ref_path /= name + ".png";
				if(!std::filesystem::exists(ref_path))
					return;
				_reference = IMG_LoadTexture(renderer.getNativeRenderer(), ref_path.string().c_str());
			}
			inline void setRenderData(void* mlx, void* win) noexcept { _mlx = mlx; _win = win; }
			inline const std::string& getName() const noexcept { return _name; }
			inline SDL_Texture* getResult() const noexcept { return _result; }
			inline SDL_Texture* getReference() const noexcept { return _reference; }
			inline void destroyResult() noexcept { SDL_DestroyTexture(_result); _result = nullptr; }
			inline void setResultTexture(SDL_Texture* result) noexcept { _result = result; }
			virtual void setup() {};
			virtual void run() = 0;
			virtual void cleanup() {};
			virtual ~BaseTest() { destroyResult(); SDL_DestroyTexture(_reference); }

		protected:
			std::string _name;
			void* _mlx = nullptr;
			void* _win = nullptr;
			SDL_Texture* _reference = nullptr;
			SDL_Texture* _result = nullptr;
	};
}

#endif

#ifndef MLX_UT_GRAPHICS_UTILS
#define MLX_UT_GRAPHICS_UTILS

#include <PreCompiled.h>

namespace mlxut
{
	void ImageZoom(SDL_Texture* texture, ImVec2 size, ImVec2 cursor_pos, float zoom = 4.0f, float region_size = 32.0f);
}

#endif

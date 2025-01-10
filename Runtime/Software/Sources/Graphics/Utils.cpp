#include <Graphics/Utils.h>

namespace mlxut
{
	void ImageZoom(SDL_Texture* texture, ImVec2 size, ImVec2 cursor_pos, float zoom, float region_size)
	{
		if(ImGui::BeginItemTooltip())
		{
			const float zoom = 4.0f;
			const float region_sz = 32.0f;

			float region_x = ImGui::GetIO().MousePos.x - cursor_pos.x - region_sz * 0.5f;
			float region_y = ImGui::GetIO().MousePos.y - cursor_pos.y - region_sz * 0.5f;

			if(region_x < 0.0f)
				region_x = 0.0f;
			else if(region_x > size.x - region_sz)
				region_x = size.x - region_sz;
			if(region_y < 0.0f)
				region_y = 0.0f;
			else if(region_y > size.y - region_sz)
				region_y = size.y - region_sz;

			ImGui::Text("Min: (%.2f, %.2f)", region_x, region_y);
			ImGui::Text("Max: (%.2f, %.2f)", region_x + region_sz, region_y + region_sz);
			ImVec2 uv0 = ImVec2((region_x) / size.x, (region_y) / size.y);
			ImVec2 uv1 = ImVec2((region_x + region_sz) / size.x, (region_y + region_sz) / size.y);
			ImGui::Image(static_cast<void*>(texture), ImVec2(region_size * zoom, region_size * zoom), uv0, uv1);
			ImGui::EndTooltip();
		}
	}
}

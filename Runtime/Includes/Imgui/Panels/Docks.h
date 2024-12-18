#ifndef MLX_UT_DOCKS
#define MLX_UT_DOCKS

#include <Pch.h>
#include <Imgui/Panels/Panel.h>

namespace mlxut
{
	class Docks : public Panel
	{
		public:
			Docks();
			void OnUpdate(ivec2 size) override;
			~Docks() override = default;
	};
}

#endif

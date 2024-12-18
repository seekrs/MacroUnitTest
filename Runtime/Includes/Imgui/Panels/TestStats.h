#ifndef MLX_UT_TEST_STATS
#define MLX_UT_TEST_STATS

#include <Pch.h>
#include <Imgui/Panels/Panel.h>

namespace mlxut
{
	class TestStats : public Panel
	{
		public:
			TestStats();
			void OnUpdate(ivec2 size) override;
			~TestStats() override = default;
	};
}

#endif

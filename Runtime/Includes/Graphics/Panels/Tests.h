#ifndef MLX_UT_TESTS_PANEL
#define MLX_UT_TESTS_PANEL

#include <Graphics/Panels/Panel.h>

namespace mlxut
{
	class TestsPanel : public Panel
	{
		public:
			TestsPanel();
			void OnUpdate(ImVec2 size) override;
			~TestsPanel() override = default;

		private:
	};
}

#endif

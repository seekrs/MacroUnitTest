#ifndef MLX_UT_TESTS_PANEL
#define MLX_UT_TESTS_PANEL

#include <Graphics/Panels/Panel.h>
#include <Tests/Tester.h>

namespace mlxut
{
	class TestsPanel : public Panel
	{
		public:
			TestsPanel(Tester& tester);
			void OnUpdate(ImVec2 size) override;
			~TestsPanel() override = default;

		private:
			Tester& m_tester;
	};
}

#endif

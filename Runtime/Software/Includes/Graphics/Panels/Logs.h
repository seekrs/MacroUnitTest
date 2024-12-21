#ifndef MLX_UT_LOGS_PANEL
#define MLX_UT_LOGS_PANEL

#include <Graphics/Panels/Panel.h>

namespace mlxut
{
	class LogsPanel : public Panel
	{
		public:
			LogsPanel(class Tester& tester);
			void OnUpdate(ImVec2 size) override;
			~LogsPanel() override = default;

		private:
			class Tester& m_tester;
	};
}

#endif

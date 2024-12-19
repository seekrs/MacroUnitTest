#ifndef MLX_UT_LOGS_PANEL
#define MLX_UT_LOGS_PANEL

#include <Graphics/Panels/Panel.h>

namespace mlxut
{
	class LogsPanel : public Panel
	{
		public:
			LogsPanel();
			void OnUpdate(ImVec2 size) override;
			~LogsPanel() override = default;

		private:
	};
}

#endif

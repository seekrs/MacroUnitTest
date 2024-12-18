#ifndef MLX_UT_PANEL_STACK
#define MLX_UT_PANEL_STACK

#include <Pch.h>
#include <Imgui/Panels/Panel.h>

namespace mlxut
{
	class PanelStack
	{
		public:
			PanelStack() = default;

			void AddPanel(std::shared_ptr<Panel> const panel);

			void RemovePanel(std::shared_ptr<Panel> const panel);
			void RemovePanel(const std::string& name);

			std::shared_ptr<Panel> GetPanel(const std::string& name);
			std::shared_ptr<Panel> GetPanel(std::size_t index);

			inline const std::vector<std::shared_ptr<Panel>>& getPanels() const { return m_panels; }

			~PanelStack() = default;

		private:
			std::vector<std::shared_ptr<Panel>> m_panels;
	};
}

#endif

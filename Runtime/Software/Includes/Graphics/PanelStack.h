#ifndef MLX_UT_PANEL_STACK
#define MLX_UT_PANEL_STACK

#include <PreCompiled.h>
#include <Graphics/Panels/Panel.h>

namespace mlxut
{
	class PanelStack
	{
		public:
			PanelStack() = default;

			void AddPanel(std::shared_ptr<Panel> panel);

			void RemovePanel(std::shared_ptr<Panel> panel);
			void RemovePanel(const std::string& name);

			std::shared_ptr<Panel> GetPanel(const std::string& name);
			std::shared_ptr<Panel> GetPanel(std::size_t index);

			[[nodiscard]] inline const std::vector<std::shared_ptr<Panel>>& GetPanels() const { return m_panels; }

			void Destroy();

			~PanelStack() = default;

		private:
			std::vector<std::shared_ptr<Panel>> m_panels;
	};
}

#endif

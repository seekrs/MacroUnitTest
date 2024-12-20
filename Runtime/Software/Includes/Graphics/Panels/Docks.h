#ifndef MLX_UT_DOCKS
#define MLX_UT_DOCKS

#include <Graphics/Panels/Panel.h>
#include <Graphics/MenuBar.h>

namespace mlxut
{
	class Docks : public Panel
	{
		public:
			Docks(const MenuBar& menubar);
			void OnUpdate(ImVec2 size) override;
			~Docks() override = default;

		private:
			const MenuBar& m_menubar;
	};
}

#endif

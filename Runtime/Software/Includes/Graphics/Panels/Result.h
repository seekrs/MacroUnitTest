#ifndef MLX_UT_RESULT_PANEL
#define MLX_UT_RESULT_PANEL

#include <Graphics/Panels/Panel.h>

namespace mlxut
{
	class Results : public Panel
	{
		public:
			Results(class Tester& tester);
			void OnUpdate(ImVec2 size) override;
			~Results() override = default;

		private:
			class Tester& m_tester;
	};
}

#endif

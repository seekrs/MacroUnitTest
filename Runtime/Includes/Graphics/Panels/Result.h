#ifndef MLX_UT_RESULT_PANEL
#define MLX_UT_RESULT_PANEL

#include <Graphics/Panels/Panel.h>

namespace mlxut
{
	class Results : public Panel
	{
		public:
			Results();
			void OnUpdate(ImVec2 size) override;
			~Results() override = default;

		private:
	};
}

#endif

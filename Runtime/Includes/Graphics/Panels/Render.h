#ifndef MLX_UT_RENDER
#define MLX_UT_RENDER

#include <Graphics/Panels/Panel.h>

namespace mlxut
{
	class Render : public Panel
	{
		public:
			Render();
			void OnUpdate(ImVec2 size) override;
			~Render() override = default;

		private:
	};
}

#endif

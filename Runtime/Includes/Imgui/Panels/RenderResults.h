#ifndef MLX_UT_RENDER_RESULTS
#define MLX_UT_RENDER_RESULTS

#include <Pch.h>
#include <Imgui/Panels/Panel.h>

namespace mlxut
{
	class RenderResults : public Panel
	{
		public:
			RenderResults(NonOwningPtr<class Tester> tester, const class Renderer& renderer);
			void OnUpdate(ivec2 size) override;
			~RenderResults() override = default;

		private:
			const class Renderer& m_renderer;
			NonOwningPtr<class Tester> p_tester;
	};
}

#endif

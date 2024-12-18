#ifndef MLX_UT_MLX_INFOS
#define MLX_UT_MLX_INFOS

#include <Pch.h>
#include <Imgui/Panels/Panel.h>

namespace mlxut
{
	class MLXinfos : public Panel
	{
		public:
			MLXinfos(NonOwningPtr<class Tester> tester);
			void OnUpdate(ivec2 size) override;
			~MLXinfos() override = default;

		private:
			NonOwningPtr<class Tester> p_tester;
	};
}

#endif

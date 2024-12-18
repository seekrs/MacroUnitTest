#ifndef MLX_UT_TESTS_LIST
#define MLX_UT_TESTS_LIST

#include <Pch.h>
#include <Imgui/Panels/Panel.h>

namespace mlxut
{
	class TestList : public Panel
	{
		public:
			TestList(NonOwningPtr<class Tester> tester);
			void OnUpdate(ivec2 size) override;
			~TestList() override = default;

		private:
			NonOwningPtr<class Tester> p_tester;
	};
}

#endif

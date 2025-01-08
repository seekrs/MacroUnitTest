#ifndef MLX_UT_TESTS_ENUMS
#define MLX_UT_TESTS_ENUMS

#include <PreCompiled.h>

namespace mlxut
{
	enum class TestState
	{
		Pending = 0,
		Running,
		Succeeded,
		Failed,
		Suspicious,

		EndEnum
	};
	constexpr std::size_t TestStateCount = static_cast<std::size_t>(TestState::EndEnum);
}

#endif

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

		EndEnum
	};
	constexpr std::size_t TestStateCount = static_cast<std::size_t>(TestState::EndEnum);

	enum class TestDiffResult
	{
		Unprocessed = 0,
		Negligible,
		Acceptable,
		Unacceptable,

		EndEnum
	};
	constexpr std::size_t TestDiffResult = static_cast<std::size_t>(TestDiffResult::EndEnum);
}

#endif

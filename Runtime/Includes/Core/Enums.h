#ifndef MLX_UT_CORE_ENUMS
#define MLX_UT_CORE_ENUMS

#include <PreCompiled.h>

namespace mlxut
{
	enum class LogType
	{
		Debug = 0,
		Message,
		Warning,
		Error,
		FatalError,

		EndEnum
	};

	constexpr std::size_t LogTypeCount = static_cast<std::size_t>(LogType::EndEnum);

	enum class Event
	{
		FatalErrorEventCode,

		EndEnum
	};

	constexpr std::size_t EventCount = static_cast<std::size_t>(Event::EndEnum);
}

#endif

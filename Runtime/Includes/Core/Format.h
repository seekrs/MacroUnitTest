#ifndef MLX_UT_CORE_FORMAT
#define MLX_UT_CORE_FORMAT

#include <Pch.h>

namespace mlxut
{
	template<typename T, typename = void>
	struct IsOstreamable : std::false_type {};

	template<typename T>
	struct IsOstreamable<T, std::void_t<decltype(std::declval<std::ostream>() << std::declval<T>())>> : std::true_type {};

	template<typename... Args, std::enable_if_t<std::conjunction_v<IsOstreamable<Args>...>, int> = 0>
	auto Format(std::string_view format, const Args&... args);
}

#include <Core/Format.inl>

#endif

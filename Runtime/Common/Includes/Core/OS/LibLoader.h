#ifndef MLX_UT_OS_LIB_LOADER
#define MLX_UT_OS_LIB_LOADER

#include <PreCompiled.h>
#include <Utils/NonCopyable.h>

namespace mlxut
{
	using LibFunc = void (*)(void);
	using LibModule = void*;
	constexpr LibModule NullModule = nullptr;

	class LibLoader : public NonCopyable
	{
		public:
			LibLoader() = default;

			virtual LibFunc GetSymbol(LibModule module, const char* symbol) const = 0;

			virtual LibModule Load(const std::filesystem::path& path) = 0;
			virtual void UnloadLib(LibModule module) = 0;

			~LibLoader() = default;
	};
}

#endif

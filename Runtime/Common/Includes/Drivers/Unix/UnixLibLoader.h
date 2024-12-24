#ifndef MLX_UT_DRIVERS_UNIX_LIB_LOADER
#define MLX_UT_DRIVERS_UNIX_LIB_LOADER

#include <Drivers/Unix/PreCompiled.h>
#include <Core/OS/LibLoader.h>

namespace mlxut
{
	class UnixLibLoader : public LibLoader
	{
		public:
			UnixLibLoader() = default;

			[[nodiscard]]
			LibFunc GetSymbol(LibModule module, const char* symbol) const override;

			[[nodiscard]]
			LibModule Load(const std::filesystem::path& path) override;
			void UnloadLib(LibModule module) override;

			~UnixLibLoader() = default;
	};
}

#endif

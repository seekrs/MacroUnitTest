#ifndef MLX_UT_DRIVERS_WINDOWS_LIB_LOADER
#define MLX_UT_DRIVERS_WINDOWS_LIB_LOADER

#include <Drivers/Windows/PreCompiled.h>
#include <Core/OS/LibLoader.h>

namespace mlxut
{
	class WindowsLibLoader : public LibLoader
	{
		public:
			WindowsLibLoader() = default;

			[[nodiscard]]
			LibFunc GetSymbol(LibModule module, const char* symbol) const override;

			[[nodiscard]]
			LibModule Load(const std::filesystem::path& path) override;
			void UnloadLib(LibModule module) override;

			~WindowsLibLoader() = default;
	};
}

#endif

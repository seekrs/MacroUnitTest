#ifndef MLX_UT_DRIVERS_MACOS_LIB_LOADER
#define MLX_UT_DRIVERS_MACOS_LIB_LOADER

#include <Drivers/MacOS/PreCompiled.h>
#include <Core/OS/LibLoader.h>

namespace mlxut
{
	class MacOSLibLoader : public LibLoader
	{
		public:
			MacOSLibLoader() = default;

			[[nodiscard]]
			LibFunc GetSymbol(LibModule module, const char* symbol) const override;

			[[nodiscard]]
			LibModule Load(const std::filesystem::path& path) override;
			void UnloadLib(LibModule module) override;

			~MacOSLibLoader() = default;

		private:
			void* m_handle = nullptr;
	};
}

#endif

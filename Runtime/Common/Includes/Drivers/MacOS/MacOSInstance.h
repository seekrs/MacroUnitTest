#ifndef MLX_UT_DRIVERS_MACOS_INSTANCE
#define MLX_UT_DRIVERS_MACOS_INSTANCE

#include <Drivers/MacOS/PreCompiled.h>
#include <Core/OS/OSInstance.h>

namespace mlxut
{
	class MacOSInstance final : public OSInstance
	{
		public:
			MacOSInstance() = default;

			void Init(int ac, char** av);
			void Shutdown() override;

			[[nodiscard]]
			std::filesystem::path GetExecutablePath() override;
			[[nodiscard]]
			std::filesystem::path GetCurrentWorkingDirectoryPath() override;
			bool OpenURL([[maybe_unused]] const std::string& url) override;
			void Delay(std::uint32_t us) override;

			~MacOSInstance() override = default;
	};
}

#endif

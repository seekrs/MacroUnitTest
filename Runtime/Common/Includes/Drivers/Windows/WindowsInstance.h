#ifndef MLX_UT_DRIVERS_WINDOWS_INSTANCE
#define MLX_UT_DRIVERS_WINDOWS_INSTANCE

#include <Drivers/Windows/PreCompiled.h>
#include <Core/OS/OSInstance.h>

namespace mlxut
{
	class WindowsInstance final : public OSInstance
	{
		public:
			WindowsInstance() = default;

			void Init(int ac, char** av);
			void Shutdown() override;

			[[nodiscard]]
			std::filesystem::path GetExecutablePath() override;
			[[nodiscard]]
			std::filesystem::path GetCurrentWorkingDirectoryPath() override;
			bool OpenURL(const std::string& url) override;
			void Delay(std::uint32_t us) override;

			~WindowsInstance() = default;
	};
}

#endif

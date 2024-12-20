#ifndef MLX_UT_DRIVERS_UNIX_INSTANCE
#define MLX_UT_DRIVERS_UNIX_INSTANCE

#include <Drivers/Unix/PreCompiled.h>
#include <Core/OS/OSInstance.h>

namespace mlxut
{
	class UnixInstance final : public OSInstance
	{
		public:
			UnixInstance() = default;

			void Init(int ac, char** av);
			void Shutdown() override;

			[[nodiscard]]
			std::filesystem::path GetExecutablePath() override;
			[[nodiscard]]
			std::filesystem::path GetCurrentWorkingDirectoryPath() override;
			bool OpenURL([[maybe_unused]] const std::string& url) override;
			void Delay(std::uint32_t us) override;

			~UnixInstance() override = default;

		private:
			char** m_av = nullptr;
			int m_ac;
	};
}

#endif

#ifndef MLX_UT_TEST
#define MLX_UT_TEST

#include <PreCompiled.h>
#include <Tests/Enums.h>

namespace mlxut
{
	class Test
	{
		public:
			Test(const class Renderer& renderer, std::string name);

			void Reset() noexcept;

			void Run(std::filesystem::path mlx_path);
			bool IsTestFinished();

			[[nodiscard]] inline SDL_Texture* GetResult() const noexcept { return p_result; }
			[[nodiscard]] inline SDL_Texture* GetReference() const noexcept { return p_reference; }

			[[nodiscard]] inline const std::string& GetName() const noexcept { return m_name; }
			[[nodiscard]] inline const std::string& GetLogs() const noexcept { return m_logs; }

			[[nodiscard]] inline bool IsPending() const noexcept { return m_state == TestState::Pending; }
			[[nodiscard]] inline bool IsRunning() const noexcept { return m_state == TestState::Running; }
			[[nodiscard]] inline bool HasPassed() const noexcept { return m_state == TestState::Succeeded; }
			[[nodiscard]] inline bool HasFailed() const noexcept { return m_state == TestState::Failed; }

		private:
			std::vector<std::uint32_t> m_result_pixels;
			std::vector<std::uint32_t> m_reference_pixels;

			std::string m_logs;
			std::string m_name;

			std::unique_ptr<TinyProcessLib::Process> p_process;

			const class Renderer& m_renderer;

			SDL_Texture* p_reference = nullptr;
			SDL_Texture* p_result = nullptr;

			TestState m_state;
	};
}

#endif

#ifndef MLX_UT_TESTER
#define MLX_UT_TESTER

#include <PreCompiled.h>
#include <Tests/Test.h>

namespace mlxut
{
	class Tester
	{
		public:
			Tester() = default;

			void CreateAllTests(const class Renderer& renderer);
			void RunAllTests(const std::filesystem::path& mlx_path);
			bool HaveAllTestsFinished();

			const auto& GetAllTests() const noexcept { return m_tests; }
			inline bool AreTestsRunning() const noexcept { return m_is_running; }
			inline std::size_t GetTestsPassedNumber() const noexcept { return m_passed_tests; }
			inline std::size_t GetTestsFailedNumber() const noexcept { return m_failed_tests; }
			inline std::size_t GetTestsPendingNumber() const noexcept { return m_pending_tests; }

			~Tester() = default;

		private:
			std::vector<std::shared_ptr<Test>> m_tests;
			std::size_t m_passed_tests = 0;
			std::size_t m_failed_tests = 0;
			std::size_t m_pending_tests = 0;
			bool m_is_running = false;
	};
}

#endif

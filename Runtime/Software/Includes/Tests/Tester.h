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
			void RunSingleTests(std::size_t index, const std::filesystem::path& mlx_path);
			bool HaveAllTestsFinished();
			void FetchAllResults();
			void CreateAllRenderTextures();
			void ComputeAllErrorMaps();
			void FetchSuccess();
			void Reset();

			[[nodiscard]] std::vector<std::shared_ptr<Test>>& GetAllTests() noexcept { return m_tests; }
			[[nodiscard]] inline bool AreTestsRunning() const noexcept { return m_is_running; }
			[[nodiscard]] inline std::size_t GetTestsPassedNumber() const noexcept { return m_passed_tests; }
			[[nodiscard]] inline std::size_t GetTestsFailedNumber() const noexcept { return m_failed_tests; }
			[[nodiscard]] inline std::size_t GetTestsSuspiciousNumber() const noexcept { return m_sus_tests; }
			[[nodiscard]] inline std::size_t GetTestsPendingNumber() const noexcept { return m_pending_tests; }
			[[nodiscard]] inline std::size_t GetSelectedTest() const noexcept { return m_selected_test; }

			inline void SelectTest(std::size_t index) { if(index < m_tests.size()) m_selected_test = index; }
			inline void SelectTest(std::string_view name)
			{
				for(std::size_t i = 0; i < m_tests.size(); i++)
				{
					if(m_tests[i]->GetName() == name)
					{
						m_selected_test = i;
						return;
					}
				}
			}

			~Tester() = default;

		private:
			std::vector<std::shared_ptr<Test>> m_tests;
			std::size_t m_selected_test = 0;
			std::size_t m_passed_tests = 0;
			std::size_t m_failed_tests = 0;
			std::size_t m_sus_tests = 0;
			std::size_t m_pending_tests = 0;
			bool m_is_running = false;
	};
}

#endif

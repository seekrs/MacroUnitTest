#ifndef MLX_UT_FILE_DIALOG
#define MLX_UT_FILE_DIALOG

#include <PreCompiled.h>

namespace mlxut
{
	class FileDialog
	{
		public:
			FileDialog() = default;

			void Open(std::string title, std::vector<std::string> types);
			bool IsFinished();
			std::filesystem::path GetResult();

			~FileDialog() = default;

		private:
			std::unique_ptr<pfd::open_file> p_dialog;
			std::filesystem::path m_last_path;
	};
}

#endif

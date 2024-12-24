#include <Core/FileDialog.h>

namespace mlxut
{
	void FileDialog::Open(std::string title, std::vector<std::string> types)
	{
		if(!IsFinished())
			return;
		p_dialog.reset();
		p_dialog = std::make_unique<pfd::open_file>(std::move(title), m_last_path.string(), std::move(types));
	}

	bool FileDialog::IsFinished()
	{
		if(!p_dialog)
			return false;
		return p_dialog->ready();
	}

	std::filesystem::path FileDialog::GetResult()
	{
		if(!p_dialog)
			return {};
		while(!IsFinished());
		auto res = p_dialog->result();
		if(res.empty())
			return {};
		std::filesystem::path path = res[0];
		m_last_path = path.parent_path();
		return path;
	}
}

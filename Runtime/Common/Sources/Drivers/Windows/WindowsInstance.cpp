#include <Drivers/Windows/WindowsLibLoader.h>
#include <Drivers/Windows/WindowsInstance.h>
#include <Core/CLI.h>

namespace mlxut
{
	void WindowsInstance::Init(int ac, char** av)
	{
		OSInstance::SetInstance(this);
		OSInstance::SetLibLoader(new WindowsLibLoader);
		CommandLineInterface::Get().Feed(ac, av);
	}

	void WindowsInstance::Shutdown()
	{
		OSInstance::SetInstance(nullptr);
		delete &OSInstance::GetLibLoader();
		OSInstance::SetLibLoader(nullptr);
	}

	[[nodiscard]]
	std::filesystem::path WindowsInstance::GetExecutablePath()
	{
		WCHAR path[MAX_PATH];
		GetModuleFileNameW(NULL, path, MAX_PATH);

		std::string converted_string = std::filesystem::path(path).string();
		std::replace(converted_string.begin(), converted_string.end(), '\\', '/');

		return converted_string;
	}

	[[nodiscard]]
	std::filesystem::path WindowsInstance::GetCurrentWorkingDirectoryPath()
	{
		return std::filesystem::current_path();
	}

	bool WindowsInstance::OpenURL(const std::string& url)
	{
		ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
	}

	void WindowsInstance::Delay(std::uint32_t us)
	{
		HANDLE timer;
		LARGE_INTEGER li;
		if(!(timer = CreateWaitableTimer(NULL, TRUE, NULL)))
			return;
		li.QuadPart = -(static_cast<std::uint64_t>(us) * 1000);
		if(SetWaitableTimer(timer, &li, 0, NULL, NULL, FALSE))
			WaitForSingleObject(timer, INFINITE);
		CloseHandle(timer);
	}
}

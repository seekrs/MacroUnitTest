#include <Drivers/MacOS/MacOSLibLoader.h>
#include <Drivers/MacOS/MacOSInstance.h>
#include <Core/CLI.h>

#import <Cocoa/Cocoa.h>

namespace mlxut
{
	void MacOSInstance::Init(int ac, char** av)
	{
		OSInstance::SetInstance(this);
		OSInstance::SetLibLoader(new MacOSLibLoader);
		CommandLineInterface::Get().Feed(ac, av);
	}

	void MacOSInstance::Shutdown()
	{
		OSInstance::SetInstance(nullptr);
		delete &OSInstance::GetLibLoader();
		OSInstance::SetLibLoader(nullptr);
	}

	[[nodiscard]]
	std::filesystem::path MacOSInstance::GetExecutablePath()
	{
		std::uint32_t size = 0;
		_NSGetExecutablePath(nullptr, &size);

		std::vector<char> buffer;
		buffer.resize(size + 1);

		_NSGetExecutablePath(buffer.data(), &size);
		buffer[size] = '\0';

		if(!std::strrchr(buffer.data(), '/'))
			return std::filesystem::path{};
		return std::filesystem::path{buffer.data()};
	}

	[[nodiscard]]
	std::filesystem::path MacOSInstance::GetCurrentWorkingDirectoryPath()
	{
		return GetExecutablePath().parent_path();
	}

	bool MacOSInstance::OpenURL([[maybe_unused]] const std::string& url)
	{
		using namespace std::literals;
		std::string command = "xdg-open"s + url;
		return std::system(command.c_str()) == 0;
	}

	void MacOSInstance::Delay(std::uint32_t us)
	{
		struct timespec requested = { static_cast<time_t>(us / 1000000), (static_cast<long>(us) % 1000000) * 1000 };
		struct timespec remaining;
		while(nanosleep(&requested, &remaining) == -1)
		{
			requested.tv_sec  = remaining.tv_sec;
			requested.tv_nsec = remaining.tv_nsec;
		}
	}
}

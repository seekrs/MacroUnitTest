#include <Core/CompilationProfile.h>
#include <Core/CLI.h>
#include <Core/Application.h>

#if defined(MLX_UT_PLAT_WINDOWS)

	#include <Drivers/Windows/WindowsInstance.h>

	int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
	{
		mlxut::CommandLineInterface cli;
		mlxut::WindowsInstance os;
		os.Init(0, nullptr);
		mlxut::Application app;
		app.Run();
		os.Shutdown();
		return 0;
	}

#elif defined(MLX_UT_PLAT_UNIX)

	#include <Drivers/Unix/UnixInstance.h>

	int main(int ac, char** av)
	{
		mlxut::CommandLineInterface cli;
		mlxut::UnixInstance os;
		os.Init(ac, av);
		mlxut::Application app;
		int return_code = app.Run();
		os.Shutdown();
		return return_code;
	}

#elif defined(MLX_UT_PLAT_MACOS)

	#include <Drivers/MacOS/MacOSInstance.h>

	int main(int ac, char** av)
	{
		mlxut::CommandLineInterface cli;
		mlxut::MacOSInstance os;
		os.Init(ac, av);
		mlxut::Application app;
		app.Run();
		os.Shutdown();
		return 0;
	}

#else
	#error "unknown platform"
#endif

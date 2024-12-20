#include <PreCompiled.h>
#include <Core/CompilationProfile.h>
#include <Core/CLI.h>
#include <Loader/Loader.h>

#if defined(MLX_UT_PLAT_WINDOWS)
	#include <Drivers/Windows/WindowsInstance.h>
#elif defined(MLX_UT_PLAT_UNIX)
	#include <Drivers/Unix/UnixInstance.h>
#elif defined(MLX_UT_PLAT_MACOS)
	#include <Drivers/MacOS/MacOSInstance.h>
#endif

#if defined(MLX_UT_PLAT_WINDOWS)
	int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
#else
	int main(int ac, char** av)
#endif
{
	mlxut::CommandLineInterface cli;

	#if defined(MLX_UT_PLAT_WINDOWS)
			mlxut::WindowsInstance os;
	#elif defined(MLX_UT_PLAT_UNIX)
		mlxut::UnixInstance os;
	#elif defined(MLX_UT_PLAT_MACOS)
			mlxut::MacOSInstance os;
	#endif

	os.Init(ac, av);

	auto mlx_path = mlxut::CommandLineInterface::Get().GetOption("path");
	if(!mlx_path.has_value() || !std::filesystem::exists(*mlx_path))
	{
		std::cerr << "invalid mlx path " << *mlx_path << std::endl;
		return 1;
	}

	mlxut::MLXLoader loader;
	loader.Load(*mlx_path);

	loader.Unload();
	os.Shutdown();
	return 0;
}

#include <PreCompiled.h>
#include <Core/CompilationProfile.h>
#include <Core/CLI.h>
#include <Loader/Loader.h>
#include <Scripting/Loader.h>
#include <Utils/Ansi.h>
#include <filesystem>

#if defined(MLX_UT_PLAT_WINDOWS)
	#include <Drivers/Windows/WindowsInstance.h>
#elif defined(MLX_UT_PLAT_UNIX)
	#include <Drivers/Unix/UnixInstance.h>
#elif defined(MLX_UT_PLAT_MACOS)
	#include <Drivers/MacOS/MacOSInstance.h>
#endif

int main(int ac, char** av)
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

	#ifndef MLX_UT_EMBED_TESTS
		auto script_path = mlxut::CommandLineInterface::Get().GetOption("script-path");
		if(!script_path.has_value() || !std::filesystem::exists(*script_path))
		{
			std::cerr << mlxut::Ansi::red << "Error: " << mlxut::Ansi::def << "invalid script path " << *script_path << std::endl;
			return 1;
		}
	#else
		auto script_name = mlxut::CommandLineInterface::Get().GetOption("script");
		if(!script_name.has_value())
		{
			std::cerr << mlxut::Ansi::red << "Error: " << mlxut::Ansi::def << "invalid script name" << std::endl;
			return 1;
		}
	#endif

	auto mlx_path = mlxut::CommandLineInterface::Get().GetOption("path");
	if(!mlx_path.has_value() || !std::filesystem::exists(*mlx_path))
	{
		std::cerr << mlxut::Ansi::red << "Error: " << mlxut::Ansi::def << "invalid mlx path " << *mlx_path << std::endl;
		return 1;
	}

	mlxut::MLXLoader mlx_loader;
	mlx_loader.Load(*mlx_path);

	mlxut::LuaLoader lua_loader;
	#ifndef MLX_UT_EMBED_TESTS
		auto script = lua_loader.LoadScript(*script_path);
	#else
		auto script = lua_loader.LoadScript(*script_name);
	#endif

	if(script.has_value())
	{
		mlx_context mlx = mlx_loader.mlx_init();
		mlx_image render_target = mlx_loader.mlx_new_image(mlx, MLX_WIN_WIDTH, MLX_WIN_HEIGHT);
		mlx_window_create_info create_infos{};
		create_infos.render_target = render_target;
		mlx_window window = mlx_loader.mlx_new_window(mlx, &create_infos);

		struct LoopData
		{
			mlx_context mlx;
			mlx_window window;
			mlxut::LuaScript& script;
			mlxut::MLXLoader& loader;

			LoopData(mlx_context mlx, mlx_window window, mlxut::LuaScript& script, mlxut::MLXLoader& loader) : mlx(mlx), window(window), script(script), loader(loader) {}
		};

		LoopData data(mlx, window, *script, mlx_loader);

		script->RunOnSetup(mlx, window);

		mlx_loader.mlx_add_loop_hook(mlx, [](void* data) -> void
		{
			LoopData* loop_data = reinterpret_cast<LoopData*>(data);
			loop_data->script.RunOnTest(loop_data->mlx, loop_data->window);
			loop_data->loader.mlx_loop_end(loop_data->mlx);
		}, &data);
		mlx_loader.mlx_loop(mlx);

		script->RunOnQuit(mlx, window);
		mlx_loader.mlx_destroy_window(mlx, window);

		{
			std::vector<mlx_color> result;
			// FIX THIS FUNCTION !!!
			//mlx_loader.mlx_get_image_region(mlx, render_target, 0, 0, MLX_WIN_WIDTH, MLX_WIN_HEIGHT, result.data());
			for(int y = 0; y < MLX_WIN_HEIGHT; y++)
			{
				for(int x = 0; x < MLX_WIN_WIDTH; x++)
					result.push_back(mlx_loader.mlx_get_image_pixel(mlx, render_target, x, y));
			}

			#ifndef MLX_UT_EMBED_TESTS
				std::filesystem::path transfer_file_path = std::filesystem::temp_directory_path() / std::filesystem::path{ *script_path }.stem();
			#else
				std::filesystem::path transfer_file_path = std::filesystem::temp_directory_path() / *script_name;
			#endif
			std::fstream transfer_file(transfer_file_path, std::ios::out | std::ios::binary | std::ios::trunc);
			if(!transfer_file.is_open())
			{
				std::cerr << mlxut::Ansi::red << "Error: " << mlxut::Ansi::def << "could not open transfer file at " << std::move(transfer_file_path) << std::endl;
				return 1;
			}
			transfer_file.write(reinterpret_cast<char*>(result.data()), result.size() * sizeof(mlx_color));
			transfer_file.close();
		}

		mlx_loader.mlx_destroy_image(mlx, render_target);
		mlx_loader.mlx_destroy_context(mlx);
	}

	mlx_loader.Unload();
	os.Shutdown();
	return 0;
}

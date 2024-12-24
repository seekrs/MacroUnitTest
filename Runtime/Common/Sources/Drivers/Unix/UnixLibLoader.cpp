#include <Drivers/Unix/UnixLibLoader.h>

namespace mlxut
{
	[[nodiscard]]
	LibFunc UnixLibLoader::GetSymbol(LibModule module, const char* symbol) const
	{
		void* ptr = dlsym(module, symbol);
		if(ptr == nullptr)
			return nullptr;
		LibFunc func;
		*(void**)(&func) = ptr;
		return func;
	}

	[[nodiscard]]
	LibModule UnixLibLoader::Load(const std::filesystem::path& path)
	{
		LibModule module;
		module = dlopen(path.string().data(), RTLD_LAZY | RTLD_GLOBAL);
		if(module == NullModule)
			return NullModule;
		return module;
	}

	void UnixLibLoader::UnloadLib(LibModule module)
	{
		if(module != NullModule)
			dlclose(module);
	}
}

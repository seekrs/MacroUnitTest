#include <Drivers/Windows/WindowsLibLoader.h>

#if defined(_MINWINDEF_)
	/* minwindef.h defines FARPROC, and attempting to redefine it may conflict with -Wstrict-prototypes */
#elif defined(_WIN64)
	typedef __int64 (__stdcall* FARPROC)(void);
#else
	typedef int (__stdcall* FARPROC)(void);
#endif
__declspec(dllimport) HMODULE __stdcall LoadLibraryA(LPCSTR);
__declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE, LPCSTR);
__declspec(dllimport) int __stdcall FreeLibrary(HMODULE);

namespace mlxut
{
	[[nodiscard]]
	LibFunc WindowsLibLoader::GetSymbol(LibModule module, const char* symbol) const
	{
		LibFunc func = reinterpret_cast<LibFunc>(::GetProcAddress(module, symbol));
		if(func == nullptr)
			return nullptr;
		return func;
	}

	[[nodiscard]]
	LibModule WindowsLibLoader::Load(const std::filesystem::path& path)
	{
		LibModule module;
		module = ::LoadLibraryA(path.string().data());
		if(module == NullModule)
			return NullModule;
		return module;
	}

	void WindowsLibLoader::UnloadLib(LibModule module)
	{
		if(module != NullModule)
			::FreeLibrary(module);
	}
}

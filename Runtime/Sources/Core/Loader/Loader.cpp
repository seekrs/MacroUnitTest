#include <Core/Loader/Loader.h>
#include <Core/OS/OSInstance.h>

namespace mlxut
{
	static inline LibFunc GetMlxProcAddr(LibModule module, const char* name)
	{
		LibFunc fn = OSInstance::GetLibLoader().GetSymbol(module, name);
		if(!fn)
			FatalError("MLXLoader: could not load '%'", name);
		return fn;
	}

	void MLXLoader::Load(std::filesystem::path path)
	{
		if(m_module != NullModule)
			Unload();
		m_module = OSInstance::GetLibLoader().Load(path);
		if(m_module == NullModule)
		{
			Error("MLXLoader: could not load %", std::move(path));
			return;
		}
		#define MLX_UT_MLX_FUNCTION(fn) fn = reinterpret_cast<PFN_##fn>(GetMlxProcAddr(m_module, #fn));
			#include <Core/Loader/Prototypes.h>
		#undef MLX_UT_MLX_FUNCTION
	}

	void MLXLoader::Unload() noexcept
	{
		OSInstance::GetLibLoader().UnloadLib(m_module);
		m_module = NullModule;
		#define MLX_UT_MLX_FUNCTION(fn) fn = nullptr;
			#include <Core/Loader/Prototypes.h>
		#undef MLX_UT_MLX_FUNCTION
	}
}

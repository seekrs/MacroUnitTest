#include <Loader/Loader.h>
#include <Core/OS/OSInstance.h>

namespace mlxut
{
	static inline LibFunc GetMlxProcAddr(LibModule module, const char* name)
	{
		LibFunc fn = OSInstance::GetLibLoader().GetSymbol(module, name);
		if(!fn)
		{
			std::cerr << "could not load " << name << std::endl;
			std::exit(1);
		}
		return fn;
	}

	void MLXLoader::Load(std::filesystem::path path)
	{
		if(m_module != NullModule)
			Unload();
		m_module = OSInstance::GetLibLoader().Load(path);
		if(m_module == NullModule)
		{
			std::cerr << "could not load " << std::move(path) << std::endl;
			return;
		}
		#define MLX_UT_MLX_FUNCTION(fn) fn = reinterpret_cast<PFN_##fn>(GetMlxProcAddr(m_module, #fn));
			#include <Loader/Prototypes.h>
		#undef MLX_UT_MLX_FUNCTION
	}

	void MLXLoader::Unload() noexcept
	{
		OSInstance::GetLibLoader().UnloadLib(m_module);
		m_module = NullModule;
		#define MLX_UT_MLX_FUNCTION(fn) fn = nullptr;
			#include <Loader/Prototypes.h>
		#undef MLX_UT_MLX_FUNCTION
	}
}

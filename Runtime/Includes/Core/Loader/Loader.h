#ifndef MLX_UT_LOADER
#define MLX_UT_LOADER

#include <PreCompiled.h>
#include <Core/Loader/PFN.h>
#include <Core/OS/LibLoader.h>

namespace mlxut
{
	class MLXLoader
	{
		public:
			inline MLXLoader() noexcept { s_instance = this; }

			void Load(std::filesystem::path path);
			void Unload() noexcept;

			inline static MLXLoader& Get() noexcept { return *s_instance; }

			inline ~MLXLoader() noexcept { s_instance = nullptr; }

			#define MLX_UT_MLX_FUNCTION(fn) PFN_##fn fn;
				#include <Core/Loader/Prototypes.h>
			#undef MLX_UT_MLX_FUNCTION
		private:
			static inline MLXLoader* s_instance = nullptr;

			LibModule m_module = NullModule;
	};
}

#endif

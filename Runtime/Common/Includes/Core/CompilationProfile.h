#ifndef MLX_UT_COMPILATION_PROFILE
#define MLX_UT_COMPILATION_PROFILE

#include <climits>
#include <cstdint>

// Try to identify the compiler
#if defined(__BORLANDC__)
	#define MLX_UT_COMPILER_BORDLAND
#elif defined(__clang__)
	#define MLX_UT_COMPILER_CLANG
	#ifdef __MINGW32__
		#define MLX_UT_COMPILER_MINGW
		#ifdef __MINGW64_VERSION_MAJOR
			#define MLX_UT_COMPILER_MINGW_W64
		#endif
	#endif
#elif defined(__GNUC__) || defined(__MINGW32__)
	#define MLX_UT_COMPILER_GCC
	#ifdef __MINGW32__
		#define MLX_UT_COMPILER_MINGW
		#ifdef __MINGW64_VERSION_MAJOR
			#define MLX_UT_COMPILER_MINGW_W64
		#endif
	#endif
#elif defined(__INTEL_COMPILER) || defined(__ICL)
	#define MLX_UT_COMPILER_INTEL
#elif defined(_MSC_VER)
	#define MLX_UT_COMPILER_MSVC
#else
	#define MLX_UT_COMPILER_UNKNOWN
	#warning "This compiler is not fully supported"
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
	#define MLX_UT_PLAT_WINDOWS
#elif defined(__linux__)
	#define MLX_UT_PLAT_LINUX
	#define MLX_UT_PLAT_UNIX
#elif defined(__APPLE__) && defined(__MACH__)
	#define MLX_UT_PLAT_MACOS
#elif defined(unix) || defined(__unix__) || defined(__unix)
	#define MLX_UT_PLAT_UNIX
#else
	#error "Unknown environment (not Windows, not Linux, not MacOS, not Unix)"
#endif

#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
	#define MLX_UT_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
	#define MLX_UT_FUNC_SIG __PRETTY_FUNCTION__
#elif (defined(__FUNCSIG__) || (_MSC_VER))
	#define MLX_UT_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
	#define MLX_UT_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
	#define MLX_UT_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
	#define MLX_UT_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
	#define MLX_UT_FUNC_SIG __func__
#else
	#define MLX_UT_FUNC_SIG "Unknown function"
#endif

#if defined(MLX_UT_PLAT_WINDOWS)
	#define MLX_UT_LIB_EXTENSION ".dll"
#elif defined(MLX_UT_PLAT_UNIX)
	#define MLX_UT_LIB_EXTENSION ".so"
#elif defined(MLX_UT_PLAT_MACOS)
	#define MLX_UT_LIB_EXTENSION ".dylib"
#endif

#ifdef MLX_UT_COMPILER_MSVC
	#define MLX_UT_LIB_PREFIX ""
#else
	#define MLX_UT_LIB_PREFIX "lib"
#endif

#if !defined(MLX_UT_NO_FORCEINLINE) && !defined(MLX_UT_FORCEINLINE)
	#if defined(MLX_UT_COMPILER_CLANG) || defined(MLX_UT_COMPILER_GCC)
		#define MLX_UT_FORCEINLINE __attribute__((always_inline)) inline
	#elif defined(MLX_UT_COMPILER_MSVC)
		#define MLX_UT_FORCEINLINE __forceinline
	#else
		#define MLX_UT_FORCEINLINE inline
	#endif
#endif

#if !defined(MLX_UT_NO_WEAK) && !defined(MLX_UT_WEAK)
	#if defined(MLX_UT_COMPILER_CLANG) || defined(MLX_UT_COMPILER_GCC)
		#define MLX_UT_WEAK __attribute__((weak))
	#else
		#define MLX_UT_WEAK
	#endif
#endif

#if defined(__x86_64__) || defined(_M_X64) || defined(__ppc64__)
	#define MLX_UT_64BITS
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
	#define MLX_UT_32BITS
#elif UINTPTR_MAX == UINT32_MAX
	#define MLX_UT_32BITS
#elif UINTPTR_MAX == UINT64_MAX
	#define MLX_UT_64BITS
#endif

#define MLX_UT_UNUSED_PARAM(x)
#define MLX_UT_UNUSED(x) (void)(x)

// Checking common assumptions

#if !defined(MLX_UT_32BITS) && !defined(MLX_UT_64BITS)
	#error "UnitTester can only run on 32bit or 64bit architectures"
#endif

static_assert(CHAR_BIT == 8, "CHAR_BIT is expected to be 8");

static_assert(sizeof(int8_t)  == 1, "int8_t is not of the correct size" );
static_assert(sizeof(int16_t) == 2, "int16_t is not of the correct size");
static_assert(sizeof(int32_t) == 4, "int32_t is not of the correct size");
static_assert(sizeof(int64_t) == 8, "int64_t is not of the correct size");

static_assert(sizeof(uint8_t)  == 1, "uint8_t is not of the correct size" );
static_assert(sizeof(uint16_t) == 2, "uint16_t is not of the correct size");
static_assert(sizeof(uint32_t) == 4, "uint32_t is not of the correct size");
static_assert(sizeof(uint64_t) == 8, "uint64_t is not of the correct size");

#endif

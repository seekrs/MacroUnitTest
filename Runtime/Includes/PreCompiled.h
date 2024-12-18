#ifndef MLX_UT_PCH
#define MLX_UT_PCH

#include <Core/CompilationProfile.h>

#include <vector>
#include <array>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdarg>
#include <cstdint>
#include <utility>
#include <algorithm>
#include <filesystem>
#include <unordered_map>
#include <memory>
#include <sstream>
#include <cstring>
#include <optional>
#include <mutex>
#include <csignal>

#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>

#include <portable-file-dialogs.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

#include <Utils/Vec2.h>
#include <Utils/NonOwningPtr.h>
#include <Core/Logs.h>

constexpr const std::uint16_t MLX_UT_WINDOW_WIDTH = 1280;
constexpr const std::uint16_t MLX_UT_WINDOW_HEIGHT = 750;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	constexpr const std::uint32_t rmask = 0xff000000;
	constexpr const std::uint32_t gmask = 0x00ff0000;
	constexpr const std::uint32_t bmask = 0x0000ff00;
	constexpr const std::uint32_t amask = 0x000000ff;
#else
	constexpr const std::uint32_t rmask = 0x000000ff;
	constexpr const std::uint32_t gmask = 0x0000ff00;
	constexpr const std::uint32_t bmask = 0x00ff0000;
	constexpr const std::uint32_t amask = 0xff000000;
#endif

constexpr const std::uint16_t MLX_WIN_WIDTH = 400;
constexpr const std::uint16_t MLX_WIN_HEIGHT = 400;
constexpr int RESIZE_MARGIN = 7;

#endif
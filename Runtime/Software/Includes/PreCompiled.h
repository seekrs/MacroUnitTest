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
#include <unordered_set>
#include <memory>
#include <sstream>
#include <cstring>
#include <optional>
#include <mutex>
#include <csignal>
#include <fstream>

#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>

#include <imspinner.h>

#include <process.hpp>

#include <portable-file-dialogs.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <Utils/Vec2.h>
#include <Utils/NonOwningPtr.h>
#include <Core/Logs.h>

constexpr const std::uint16_t MLX_UT_WINDOW_WIDTH = 1280;
constexpr const std::uint16_t MLX_UT_WINDOW_HEIGHT = 750;

#if SDL_BYTEORDER != SDL_BIG_ENDIAN
	constexpr const std::uint32_t R_MASK = 0xFF000000;
	constexpr const std::uint32_t G_MASK = 0x00FF0000;
	constexpr const std::uint32_t B_MASK = 0x0000FF00;
	constexpr const std::uint32_t A_MASK = 0x000000FF;
#else
	constexpr const std::uint32_t R_MASK = 0x000000FF;
	constexpr const std::uint32_t G_MASK = 0x0000FF00;
	constexpr const std::uint32_t B_MASK = 0x00FF0000;
	constexpr const std::uint32_t A_MASK = 0xFF000000;
#endif

constexpr const std::uint16_t MLX_WIN_WIDTH = 400;
constexpr const std::uint16_t MLX_WIN_HEIGHT = 400;

constexpr int RESIZE_MARGIN = 7;

constexpr float MEAN_THRESHOLD = 0.01f;
constexpr float SUSPICIOUS_THRESHOLD = 0.001f;

#endif

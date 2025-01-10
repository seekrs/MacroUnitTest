add_repositories("local-repo Xmake")

add_requires("imgui v1.91.0-docking", { configs = { sdl2 = true }})
add_requires("libsdl", "pfd", "libsdl_image", "sol2", "tiny-process-library")

add_rules("mode.debug", "mode.release", "mode.releasedbg")
set_languages("cxx20")

if is_mode("debug") then
	add_defines("MLX_UT_DEBUG")
else
	add_defines("MLX_UT_RELEASE")
	set_fpmodels("fast")
	add_vectorexts("sse", "sse2", "sse3", "ssse3")
end

set_objectdir("build/Objs/$(os)_$(arch)")
set_targetdir("build/Bin/$(os)_$(arch)")
set_rundir("build/Bin/$(os)_$(arch)")
set_dependir("build/.deps")

set_optimize("fastest")

local os_interfaces = {
	Unix = {
		dir = "Drivers/",
		enabled = is_plat("linux")
	},
	MacOS = {
		dir = "Drivers/",
		enabled = is_plat("macosx"),
		custom = function(subdir)
			add_files("Runtime/" .. subdir .. "/Sources/Drivers/MacOS/**.mm")
		end
	},
	Windows = {
		dir = "Drivers/",
		enabled = is_plat("windows") or is_plat("mingw")
	}
}

option("unitybuild", { description = "Build the app using unity build", default = false })
option("editor", { description = "Build the app in edtior mode", default = is_mode("debug") })

if not is_mode("debug") and not has_config("editor") then
	add_defines("MLX_UT_EMBED_TESTS")
end

function CreateEmbeddedResources(target)
	if is_mode("debug") and not os.exists("$(buildir)/Bin/$(os)_$(arch)/Resources") then
		os.ln("$(scriptdir)/Resources", "$(buildir)/Bin/$(os)_$(arch)/Resources")
		print("Created resources symlink")
	end
	if not is_mode("debug") then
		if os.exists("Runtime/Software/Includes/Embedded") then
			os.rm("Runtime/Software/Includes/Embedded")
		end
		os.mkdir("Runtime/Software/Includes/Embedded")
		io.writefile("Runtime/Software/Includes/Embedded/Logo.h", [[
#ifndef MLX_UT_EMBEDDED_LOGO
#define MLX_UT_EMBEDDED_LOGO

// Generated File

#include <vector>
#include <cstdint>

static const std::vector<std::uint8_t> logo_data = {
	#include <Logo.png.h>
};

#endif // MLX_UT_EMBEDDED_LOGO]])

		local references = ""
		local references_names = ""

		for _, file in ipairs(os.files("Resources/Assets/TestsReferences/*.png")) do
			_, filename, _ = file:match("^(.-)([^\\/]-)%.([^\\/%.]-)%.?$")
			references = references .. "static const std::vector<std::uint8_t> " .. filename .. "_data = {\n\t#include <" .. filename .. ".png.h>\n};\n"
			references_names = references_names .. "if(name == \"" .. filename .. "\")\n\t\treturn " .. filename .. "_data;\n\t"
		end

		io.writefile("Runtime/Software/Includes/Embedded/References.h", [[
#ifndef MLX_UT_EMBEDDED_REFERENCES
#define MLX_UT_EMBEDDED_REFERENCES

// Generated File

#include <vector>
#include <cstdint>
#include <string_view>

]] .. references ..[[

inline const std::vector<std::uint8_t> GetDataFromFilename(std::string_view name)
{
// Ugly generated function
	]] .. references_names .. [[return {};
}

#endif // MLX_UT_EMBEDDED_REFERENCES]])

		local fonts = ""

		for _, file in ipairs(os.files("Resources/Fonts/**.ttf")) do
			_, filename, _ = file:match("^(.-)([^\\/]-)%.([^\\/%.]-)%.?$")
			fonts = fonts .. "static const std::vector<std::uint8_t> " .. filename .. "_data = {\n\t#include <" .. filename .. ".ttf.h>\n};\n"
		end

		io.writefile("Runtime/Software/Includes/Embedded/Fonts.h", [[
#ifndef MLX_UT_EMBEDDED_FONTS
#define MLX_UT_EMBEDDED_FONTS

// Generated File

#include <vector>
#include <cstdint>

]] .. fonts ..[[

#endif // MLX_UT_EMBEDDED_FONTS]])

		if os.exists("Runtime/Common/Includes/Embedded") then
			os.rm("Runtime/Common/Includes/Embedded")
		end
		os.mkdir("Runtime/Common/Includes/Embedded")

		local tests = ""
		local tests_names = ""
		local array_names = ""

		for _, file in ipairs(os.files("Resources/Tests/**.lua")) do
			_, filename, _ = file:match("^(.-)([^\\/]-)%.([^\\/%.]-)%.?$")
			tests = tests .. "static const std::string " .. filename .. "_data = R\"test(\n" .. io.readfile(file) .. ")test\";\n\n"
			tests_names = tests_names .. "if(name == \"" .. filename .. "\")\n\t\treturn " .. filename .. "_data;\n\t"
			array_names = array_names .. "\"" .. filename .. "\", \n"
		end

		io.writefile("Runtime/Common/Includes/Embedded/Tests.h", [[
#ifndef MLX_UT_EMBEDDED_TESTS
#define MLX_UT_EMBEDDED_TESTS

// Generated File

#include <string>
#include <array>

static const std::array all_test_names = {
]] .. array_names .. [[
};

]] .. tests ..[[

inline const std::string GetDataFromFilename(std::string_view name)
{
// Ugly generated function
	]] .. tests_names .. [[return {};
}

#endif // MLX_UT_EMBEDDED_TESTS]])
	end
end

function ModuleTargetConfig(name, module, subdir)
	-- Add header and source files
	for _, ext in ipairs({".h", ".hpp", ".inl"}) do
		if module.dir then
			add_headerfiles("Runtime/" .. subdir .. "/Includes/" .. module.dir .. name .. "/**" .. ext)
			add_headerfiles("Runtime/" .. subdir .. "/Sources/" .. module.dir .. name .. "/**" .. ext, { prefixdir = "private", install = false })
		else
			add_headerfiles("Runtime/" .. subdir .. "/Includes/" .. name .. "/**" .. ext)
			add_headerfiles("Runtime/" .. subdir .. "/Sources/" .. name .. "/**" .. ext, { prefixdir = "private", install = false })
		end
	end

	if module.dir then
		remove_headerfiles("Runtime/" .. subdir .. "/Sources/" .. module.dir .. name .. "/Resources/**.h")
	else
		remove_headerfiles("Runtime/" .. subdir .. "/Sources/" .. name .. "/Resources/**.h")
	end

	if is_plat("windows", "linux", "macosx") then
		if module.dir then
			set_pcxxheader("Runtime/" .. subdir .. "/Includes/" .. module.dir .. name .. "/PreCompiled.h")
		else
			set_pcxxheader("Runtime/" .. subdir .. "/Includes/" .. name .. "/PreCompiled.h")
		end
	end

	if module.packages then
		add_packages(table.unpack(module.packages))
	end

	if module.publicPackages then
		for _, pkg in ipairs(module.publicPackages) do
			add_packages(pkg, { public = true })
		end
	end

	if module.deps then
		add_deps(table.unpack(module.deps))
	end

	if module.dir then
		add_files("Runtime/" .. subdir .. "/Sources/" .. module.dir .. name .. "/**.cpp")
	else
		add_files("Runtime/" .. subdir .. "/Sources/" .. name .. "/**.cpp")
	end

	if module.custom then
		module.custom(subdir)
	end
end

target("MacroUnitTest")
	set_license("MIT")
	set_kind("binary")

	add_packages("libsdl", "pfd", "libsdl_image", "imgui", "tiny-process-library")

	if not is_mode("debug") then
		add_rules("utils.bin2c", { extensions = { ".png", ".ttf" } } )
		add_files("Resources/Assets/**.png")
		add_files("Resources/Fonts/**.ttf")
	end

	if has_config("unitybuild") then
		add_rules("c++.unity_build", { batchsize = 6 })
	end

	if is_plat("windows", "linux", "macosx") then
		set_pcxxheader("Runtime/Software/Includes/PreCompiled.h")
	end
	add_includedirs("Runtime/Software/Includes", "Runtime/Software/Sources", "Runtime/ThirdParty")
	add_includedirs("Runtime/Common/Includes", "Runtime/Common/Sources")
	add_files("Runtime/Software/Sources/**.cpp|Drivers/**.cpp")

	for name, module in table.orderpairs(os_interfaces) do
		if module.enabled then
			ModuleTargetConfig(name, module, "Common")
		end
	end

	before_build(CreateEmbeddedResources)

	on_clean(function(target)
		if target:objectfiles() then
			for _, file in ipairs(target:objectfiles()) do
				if os.exists(file) then
					print("Removing " .. file)
					os.rm(file)
				end
			end
		end
		if target:targetfile() and os.exists(target:targetfile()) then
			print("Removing " .. target:targetfile())
			os.rm(target:targetfile())
		end
	end)

	add_defines("SDL_MAIN_HANDLED")
target_end()

target("TestRunner")
	set_license("MIT")
	set_kind("binary")

	add_packages("libsdl", "sol2")

	if has_config("unitybuild") then
		add_rules("c++.unity_build", { batchsize = 6 })
	end

	if is_plat("windows", "linux", "macosx") then
		set_pcxxheader("Runtime/Runner/Includes/PreCompiled.h")
	end
	add_includedirs("Runtime/Runner/Includes", "Runtime/Runner/Sources", "Runtime/ThirdParty")
	add_includedirs("Runtime/Common/Includes", "Runtime/Common/Sources")
	add_files("Runtime/Runner/Sources/**.cpp")

	for name, module in table.orderpairs(os_interfaces) do
		if module.enabled then
			ModuleTargetConfig(name, module, "Common")
		end
	end

	on_load(function(target)
		if not os.exists("$(buildir)/Bin/$(os)_$(arch)/Resources") then
			os.ln("$(scriptdir)/Resources", "$(buildir)/Bin/$(os)_$(arch)/Resources")
			print("Created resources symlink")
		end
	end)

	on_clean(function(target)
		if target:objectfiles() then
			for _, file in ipairs(target:objectfiles()) do
				if os.exists(file) then
					print("Removing " .. file)
					os.rm(file)
				end
			end
		end
		if target:targetfile() and os.exists(target:targetfile()) then
			print("Removing " .. target:targetfile())
			os.rm(target:targetfile())
		end
	end)
target_end()

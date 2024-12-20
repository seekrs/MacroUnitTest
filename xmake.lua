add_repositories("local-repo Xmake")

add_requires("imgui v1.91.0-docking", { configs = { sdl2 = true }})
add_requires("libsdl", "pfd", "libsdl_image", "sol2", "tiny-process-library")

add_rules("mode.debug", "mode.release")
set_languages("cxx20")

if is_mode("debug") then
	add_defines("MLX_UT_DEBUG")
elseif is_mode("release") then
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
		enabled = is_plat("windows")
	}
}

option("unitybuild", { description = "Build the engine using unity build", default = false })

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

	if module.dir then
		set_pcxxheader("Runtime/" .. subdir .. "/Includes/" .. module.dir .. name .. "/PreCompiled.h")
	else
		set_pcxxheader("Runtime/" .. subdir .. "/Includes/" .. name .. "/PreCompiled.h")
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

	if has_config("unitybuild") then
		add_rules("c++.unity_build", { batchsize = 6 })
	end

	set_pcxxheader("Runtime/Software/Includes/PreCompiled.h")
	add_includedirs("Runtime/Software/Includes", "Runtime/Software/Sources", "Runtime/ThirdParty")
	add_includedirs("Runtime/Common/Includes", "Runtime/Common/Sources")
	add_files("Runtime/Software/Sources/**.cpp|Drivers/**.cpp")

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

	add_defines("SDL_MAIN_HANDLED")
target_end()

target("TestRunner")
	set_license("MIT")
	set_kind("binary")

	add_packages("sol2")

	if has_config("unitybuild") then
		add_rules("c++.unity_build", { batchsize = 6 })
	end

	set_pcxxheader("Runtime/Runner/Includes/PreCompiled.h")
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

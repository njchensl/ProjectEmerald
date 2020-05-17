workspace "ProjectEmerald"
    architecture "x64"
    startproject "Runtime"

    configurations
    {
        "Debug",
        "Debug-Disassembly",
        "Release",
        "Dist"
    }

vectorextensions "AVX2"
buildoptions {
    "/Qpar", "/Qpar-report:1", "/Qvec-report:1"
}

filter "configurations:Release"
    linkoptions {
        "/LTCG"
    }
filter "configurations:Dist"
    linkoptions {
        "/LTCG"
    }


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}


project "Runtime"
    location "Runtime"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/vendor/boost"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines "EM_DEBUG"
        runtime "Debug"
        symbols "on"
        debugargs {
            "C:\\Users\\njche\\Desktop\\Test.exec"
        }

    filter "configurations:Debug-Disassembly"
        defines "EM_DEBUG"
        runtime "Debug"
        symbols "on"
        debugargs {
            "-d", "C:\\Users\\njche\\Desktop\\Test.exec"
        }

    filter "configurations:Release"
        defines "EM_RELEASE"
        runtime "Release"
        optimize "on"
        buildoptions {
            "/O2", "/Ob2", "/Ot", "/Oy", "/GT", "/GL"
        }
        debugargs {
            "C:\\Users\\njche\\Desktop\\Test.exec"
        }

    filter "configurations:Dist"
        defines "EM_DIST"
        runtime "Release"
        optimize "on"
        buildoptions {
            "/O2", "/Ob2", "/Ot", "/Oy", "/GT", "/GL"
        }
        debugargs {
            "C:\\Users\\njche\\Desktop\\Test.exec"
        }

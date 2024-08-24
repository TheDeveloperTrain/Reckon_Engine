workspace "ReckonEngine --extra"
architecture "x64"
	configurations
	{
	    "Debug",
		"Release"
	}
	project "ReckonEngine --extra"

		kind "ConsoleApp"
		language "C++"
		location "ReckonEngine --extra"

		include "Dependencies/glfw"
		
		files
		{
			"*.cpp",
			"*.h"
		}
		includedirs
		{
			"Dependencies/glfw/include/"
		}
		IncludeDir = {}
		IncludeDir["GLFW"] = "%{wks.location}/Dependencies/glfw"
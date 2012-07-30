solution "OOGL"
	configurations { "Debug", "Release" }

	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" }
		buildoptions { "-std=c++0x" } -- C++0x support REQUIRED
	configuration "Release"
		defines { "NDEBUG" }
		flags { "Optimize" }
		buildoptions { "-std=c++0x" } -- C++0x support REQUIRED

	if( _ACTION == nil ) then
		location( "build/" )
	else
		location( "build/" .. _ACTION )
	end

	libjpeg = { "src/GL/Util/libjpeg/*.c" }
	libpng = { "src/GL/Util/libpng/*.c" }
	zlib = { "src/GL/Util/zlib/*.c" }

	newoption {
		trigger			= "without-meshloader",
		description	= "Do NOT build the mesh loader"
	}

	newoption {
		trigger			= "without-imageloader",
		description	= "Do NOT build the image loader"
	}

	newoption {
		trigger			= "build",
		value				= "TYPE",
		description	= "Which type of library to output",
		allowed 		= {
				{ "shared", "Shared/Dynamic Linked" },
				{ "static", "Static linked" }
		}
	}

	if( _OPTIONS['build'] == nil ) then _OPTIONS['build'] = shared end

	configuration "without-meshloader"
		defines { "OOGL_NO_MESHLOADER" }

	configuration "without-imageloader"
		defines { "OOGL_NO_IMAGELOADER" }

	project "OOGL"
		if( _OPTIONS['build'] == "shared" ) then
			kind "SharedLib"
		else
			kind "StaticLib"
		end
		language "C++"
		includedirs { "include" }
		targetdir ( "bin/" )
		file = os.matchfiles("src/**.cpp")
		files { file }

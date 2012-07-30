solution "OOGL"
	if( _ACTION == nil ) then
		os.exit(0)
	end
	configurations { "Debug", "Release" }

	location( "build/" .. _ACTION )

	libjpeg = { "src/GL/Util/libjpeg/*.c" }
	libpng = { "src/GL/Util/libpng/*.c" }
	zlib = { "src/GL/Util/zlib/*.c" }

	newoption {
		trigger			= "with-imageloader",
		description	= "Build the image loader"
	}
	newoption {
		trigger			= "with-meshloader",
		description	= "Build the mesh loader"
	}

	project "liboogl"
		kind "SharedLib"
		language "C++"
		includedirs { "include" }
		configuration "with-imageloader"
			defines { "OOGL_USE_IMAGELOADER" }
		configuration "with-modelloader"
			defines { "OOGL_USE_MESHLOADER" }
		files { "src/**.cpp" }

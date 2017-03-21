cmake_minimum_required(VERSION 3.6)
project(metalwalrus)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        include/GL/eglew.h
        include/GL/freeglut.h
        include/GL/freeglut_ext.h
        include/GL/freeglut_std.h
        include/GL/glew.h
        include/GL/glut.h
        include/GL/glxew.h
        include/GL/wglew.h
        include/lodepng.h
        lib/lodepng.cpp
        Src/Framework/Graphics/Texture2D.cpp
        Src/Framework/Graphics/Texture2D.h
        Src/Framework/Graphics/TextureRegion.cpp
        Src/Framework/Graphics/TextureRegion.h
        Src/Framework/Graphics/VertexData.cpp
        Src/Framework/Graphics/VertexData.h
        Src/Framework/Math/Matrix3.cpp
        Src/Framework/Math/Matrix3.h
        Src/Framework/Math/Vector2.cpp
        Src/Framework/Math/Vector2.h
        Src/Framework/Util/Debug.cpp
        Src/Framework/Util/Debug.h
        Src/Framework/Util/GLError.cpp
        Src/Framework/Util/GLError.h
        Src/Framework/Util/IOUtil.cpp
        Src/Framework/Util/IOUtil.h
        Src/Framework/Util/MathUtil.cpp
        Src/Framework/Util/MathUtil.h
        Src/Framework/Game.cpp
        Src/Framework/Game.h
        Src/main.cpp)

include_directories(include)
include_directories(include/GL)

add_executable(metalwalrus ${SOURCE_FILES})
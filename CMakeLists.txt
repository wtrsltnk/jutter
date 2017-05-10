cmake_minimum_required(VERSION 3.1)

project(jutter)

option(BUILD_TESTS "Build test programs" OFF)

find_package(OpenGL REQUIRED)

set(SDL_STATIC ON)
set(SDL_SHARED OFF)
set(DIRECTX OFF CACHE BOOL "DIRECTX off")
set(SDL_SRENDER_D3D OFF CACHE BOOL "SDL_SRENDER_D3D off")
set(VIDEO_OPENGLES OFF CACHE BOOL "VIDEO_OPENGLES off")
add_subdirectory(libs/sdl2-mirror)

set(SRC_ENTITY
    src/entities/entity.cpp
    src/entities/entity.h
    src/entities/entitymanager.cpp
    src/entities/entitymanager.h
    src/entities/cameraentity.cpp
    src/entities/cameraentity.h
    src/entities/worldentity.cpp
    src/entities/worldentity.h
    )

set(SRC_UI
    src/ui/ui.cpp
    src/ui/ui.h
    src/ui/buttoncontrol.cpp
    src/ui/buttoncontrol.h
    src/ui/labelcontrol.cpp
    src/ui/labelcontrol.h
    src/ui/panelcontrol.cpp
    src/ui/panelcontrol.h
    src/ui/imagecontrol.cpp
    src/ui/imagecontrol.h
    src/ui/fadeoutlabelcontrol.cpp
    src/ui/fadeoutlabelcontrol.h
    src/ui/fadeout.cpp
    src/ui/fadeout.h
    src/ui/fadeoutswipe.cpp
    src/ui/fadeoutswipe.h
    src/ui/hintcontrol.cpp
    src/ui/hintcontrol.h
    src/ui/animatedvalue.cpp
    src/ui/animatedvalue.h
    src/ui/scorebugcontrol.cpp
    src/ui/scorebugcontrol.h
    src/ui/control.cpp
    src/ui/control.h
    src/ui/fadeablecontrol.h
    src/ui/textalignments.h
    src/ui/colors.h
    src/ui/fonts.h
    src/ui/font-icons.h
    )

set(SRC_GAMEMODES
    src/gamemodes/gamemode.cpp
    src/gamemodes/gamemode.h
    src/gamemodes/mainmenumode.cpp
    src/gamemodes/mainmenumode.h
    src/gamemodes/confirmexitgamemode.cpp
    src/gamemodes/confirmexitgamemode.h
    src/gamemodes/practicegamemode.cpp
    src/gamemodes/practicegamemode.h
    src/gamemodes/gamemodes.h
    )

set(SRC_COMMON
    src/common/geometry.cpp
    src/common/geometry.h
    src/common/postprocesseffect.cpp
    src/common/postprocesseffect.h
    src/common/shader.cpp
    src/common/shader.h
    src/common/texture.cpp
    src/common/texture.h
    src/common/randm.cpp
    src/common/randm.h
    src/common/log.cpp
    src/common/log.h
    src/common/fileio.cpp
    src/common/fileio.h
    src/common/particles.cpp
    src/common/particles.h
    src/common/timer.cpp
    src/common/timer.h
    )

set(SRC_APP
    src/system/impl-headers.cpp
    src/system/sdl2-setup.cpp
    src/system/sdl2-setup.h
    src/system/input.cpp
    src/system/input.h
    src/program.cpp
	src/gamerules.cpp
    src/gamerules.h
    src/system/iinput.h
    src/system/platform.h
    src/system/platform-opengl.h
    )

set(SHADERS
    data/shaders/gl3/geometry.vert
    data/shaders/gl3/geometry.frag
    data/shaders/gl3/effect.vert
    data/shaders/gl3/effect.frag
    data/shaders/gl3/particles.vert
    data/shaders/gl3/particles.frag
    data/shaders/gles3/geometry.vert
    data/shaders/gles3/geometry.frag
    data/shaders/gles3/effect.vert
    data/shaders/gles3/effect.frag
    data/shaders/gles3/particles.vert
    data/shaders/gles3/particles.frag
	)

add_library(nanovg
    libs/nanovg/src/nanovg.c
    libs/nanovg/src/nanovg.h
    libs/nanovg/src/nanovg_gl.h
    libs/nanovg/src/fontstash.h
    libs/nanovg/src/stb_image.h
    libs/nanovg/src/stb_truetype.h
    )

set (CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++ ${CMAKE_CXX_FLAGS}")

add_executable(jutter
    ${SRC_APP}
    ${SRC_COMMON}
    ${SRC_ENTITY}
    ${SRC_GAMEMODES}
    ${SRC_UI}
    ${STB}
	${SHADERS}
	)

target_include_directories(jutter
    PRIVATE "libs/sdl2-mirror/include"
    PRIVATE "libs/glm"
    PRIVATE "include"
    PRIVATE "${CMAKE_SOURCE_DIR}/libs/nanovg/src"
	)

target_compile_features(jutter
	PRIVATE cxx_auto_type
	PRIVATE cxx_nullptr
	PRIVATE cxx_range_for
	)

target_link_libraries(jutter
    nanovg
    SDL2-static
    ${OPENGL_LIBRARIES}
    )

if(UNIX AND NOT APPLE)
    target_link_libraries(jutter
        dl
        pthread
        GLEW
    )
endif(UNIX AND NOT APPLE)

if(BUILD_TESTS)

    add_executable(all-tests
        tests/catch.hpp
        tests/test-base.cpp
        tests/test-animatedvalue.cpp
        src/common/log.cpp
        src/common/fileio.cpp
        src/ui/animatedvalue.cpp
        )

    target_include_directories(all-tests
        PRIVATE "libs/glm"
        )

    target_compile_features(all-tests
        PRIVATE cxx_auto_type
        PRIVATE cxx_nullptr
        PRIVATE cxx_range_for
        PRIVATE cxx_thread_local
        )

endif(BUILD_TESTS)

cmake_minimum_required(VERSION 3.4.1)

string(TOLOWER ${CMAKE_BUILD_TYPE} ANDROID_BUILD_DIR)
set(DISTRIBUTION_DIR ${CMAKE_SOURCE_DIR}/android/distribution/android/SDL2/intermediates/ndkBuild)
set(SOURCE_FILES
	src/main.cpp
	src/Motherboard/gfx.cpp
	src/Motherboard/keyboard.cpp
	src/Motherboard/ports.cpp
	src/Motherboard/sound.cpp
	src/CPU/cpu.cpp
)
set(SDL_LOCATION ${CMAKE_SOURCE_DIR}/external/SDL2)

add_library( SDL2 SHARED IMPORTED )
add_library( SDL2_image SHARED IMPORTED )
add_library( SDL2_mixer SHARED IMPORTED )
set_target_properties(SDL2 PROPERTIES IMPORTED_LOCATION
${DISTRIBUTION_DIR}/${ANDROID_BUILD_DIR}/obj/local/${ANDROID_ABI}/libSDL2.so)
set_target_properties(SDL2_image PROPERTIES IMPORTED_LOCATION
${DISTRIBUTION_DIR}/${ANDROID_BUILD_DIR}/obj/local/${ANDROID_ABI}/libSDL2_image.so)
set_target_properties(SDL2_mixer PROPERTIES IMPORTED_LOCATION
${DISTRIBUTION_DIR}/${ANDROID_BUILD_DIR}/obj/local/${ANDROID_ABI}/libSDL2_mixer.so)

include_directories(${SDL_LOCATION}/SDL2/include)
include_directories(${SDL_LOCATION}/SDL2_image)
include_directories(${SDL_LOCATION}/SDL2_mixer)

add_library( main SHARED ${SDL_LOCATION}/SDL2/src/main/android/SDL_android_main.c ${SOURCE_FILES} )

target_link_libraries( main SDL2 SDL2_image SDL2_mixer )

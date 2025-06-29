# Same version requirement as SDL3
cmake_minimum_required(VERSION 3.16)

project(wordlegui LANGUAGES C VERSION "0.1.0")

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
FetchContent_Declare(
	SDL3
	GIT_REPOSITORY "https://github.com/libsdl-org/SDL"
	GIT_TAG        c9a6709bd21750f1ad9597be21abace78c6378c9  # release-3.2.16
)
FetchContent_Declare(
	SDL3_ttf
	GIT_REPOSITORY "https://github.com/libsdl-org/SDL_ttf"
	GIT_TAG        a1ce3670aec736ecbf0936c43f2f0cc53aa61e5b  # release-3.2.2
)
FetchContent_MakeAvailable(SDL3 SDL3_ttf)

# HACK: Very dirty integration of external project using Makefile
add_custom_target(build_backend
	COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR}/backend all
)
add_library(wordlebackend STATIC IMPORTED)
set_target_properties(wordlebackend PROPERTIES
	IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/backend/backend.a
)
add_dependencies(wordlebackend build_backend)
list(APPEND BACKEND_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/backend/include")
list(APPEND BACKEND_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/backend/libft/include")
include_directories(${BACKEND_INCLUDE_DIRS})

# NOTE: This target exists in case the user runs the game from the build directory.
# If the game is run using the provided Makefile, this target is useless.
add_custom_target(copy_resources
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_CURRENT_SOURCE_DIR}/res/"
		"${CMAKE_CURRENT_BINARY_DIR}/res/"
)

include_directories(include)

add_executable(wordlegui src/main.c src/logic.c src/render.c src/confetti.c)
add_dependencies(wordlegui copy_resources)
target_link_libraries(wordlegui PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf wordlebackend m)

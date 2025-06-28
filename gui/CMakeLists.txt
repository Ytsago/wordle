# Same version requirement as SDL3
cmake_minimum_required(VERSION 3.16)

project(wordlegui LANGUAGES C VERSION "0.1.0")

include(FetchContent)
FetchContent_Declare(
	SDL3
	GIT_REPOSITORY "https://github.com/libsdl-org/SDL"
	GIT_TAG        c9a6709bd21750f1ad9597be21abace78c6378c9  # release-3.2.16
)
FetchContent_MakeAvailable(SDL3)

add_executable(wordlegui src/main.c)
target_link_libraries(wordlegui PRIVATE SDL3::SDL3)

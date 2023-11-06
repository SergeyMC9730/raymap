project(raymap LANGUAGES C)

add_subdirectory(raylib)

file(GLOB_RECURSE RAYMAPSRC CONFIGURE_DEPENDS "src/raymap/*.c" "src/include/*.h")
file(GLOB_RECURSE RAYMAPTESTSRC CONFIGURE_DEPENDS "src/test/*.c")

add_library(raymap ${RAYMAPSRC})

add_executable(raymaptest ${RAYMAPTESTSRC})

target_include_directories(raymap PRIVATE src/include)
target_include_directories(raymaptest PRIVATE src/include)

target_link_libraries(raymap raylib)
target_link_libraries(raymaptest raymap)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

add_compile_options(-finput-charset=UTF-8)
add_compile_options(-fdiagnostics-color=always)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
add_compile_options(-g)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
add_compile_options(-Wl)
add_compile_options(-01)
endif()
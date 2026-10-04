cmake_minimum_required(VERSION 3.10)
project(STROOPWAFEL LANGUAGES C CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/${CMAKE_CXX_COMPILER_ID}/Debug/${CMAKE_SYSTEM_NAME}")
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/${CMAKE_CXX_COMPILER_ID}/Release/${CMAKE_SYSTEM_NAME}")


set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

message("${CMAKE_PROJECT_NAME}: Fetching binaries..")

include(FetchContent)

FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG 3.5.1)
FetchContent_Declare(glew GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git GIT_TAG glew-cmake-2.3.1)
FetchContent_Declare(glm GIT_REPOSITORY https://github.com/g-truc/glm.git GIT_TAG 1.0.3)
FetchContent_Declare(imgui GIT_REPOSITORY https://github.com/ocornut/imgui.git GIT_TAG v1.92.9b-docking)
FetchContent_Declare(tomlplusplus GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git GIT_TAG v3.4.0)
FetchContent_Declare(nfd GIT_REPOSITORY https://github.com/btzy/nativefiledialog-extended.git GIT_TAG v1.4.0)

FetchContent_MakeAvailable(glfw glew glm imgui tomlplusplus nfd)

find_package(OpenGL REQUIRED)
find_package(Git)
message("${CMAKE_PROJECT_NAME}: Binaries fetched.")

file(GLOB_RECURSE SOURCES
    src/*.cpp
    headers/*.h
)
include_directories(${CMAKE_BINARY_DIR})

if(GIT_EXECUTABLE)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} describe --tags --match "v*"
    WORKING_DIRECTORY "./"
    OUTPUT_VARIABLE GIT_DESCRIBE_VERSION
    RESULT_VARIABLE GIT_DESCRIBE_ERROR_CODE
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
  if(NOT GIT_DESCRIBE_ERROR_CODE)
    message(${GIT_DESCRIBE_VERSION})
    set(STROOPWAFEL_VERSION ${GIT_DESCRIBE_VERSION})
  endif()
endif()


configure_file(headers/StroopConfig.h.in StroopConfig.h)

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE "DEBUG=$<IF:$<CONFIG:Debug>,1,0>")

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)

set(BUILD_SHARED_LIBS OFF)

add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/headers
    ${glfw_SOURCE_DIR}/include
    ${glew_SOURCE_DIR}/include
    ${glm_SOURCE_DIR}
    ${nfd_SOURCE_DIR}
    ${tomlplusplus_SOURCE_DIR}/include
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(imgui PUBLIC
    glfw 
    OpenGL::GL
 )

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    nfd
    libglew_static
    OpenGL::GL
    imgui
)


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/res"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/res"
)
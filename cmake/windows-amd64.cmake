set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR AMD64)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # using Clang
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_C_COMPILER gcc)
    set(CMAKE_CXX_COMPILER g++)
    set(CMAKE_INSTALL_PREFIX "../out/install/GCC-UCRT64_amd64")
    add_compile_options(-finput-charset=UTF-8)


    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        #add_compile_options(-Wall)
    endif()
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(-01)
    endif()

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_C_COMPILER cl.exe)
    set(CMAKE_CXX_COMPILER cl.exe)
    set(CMAKE_INSTALL_PREFIX "../out/install/MSVC-2026_amd64")
    add_compile_options(/utf-8)

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(/Wall)
    endif()
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(/01)        
    endif()

endif()
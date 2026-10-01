#!/bin/bash
# The build script needs to be run by their operating system respectively. I don't know how to make it cross compile on one OS, so just bare with this


PS3="Select which compiler to use: "

select coms in GCC MSVC Quit
do
    case $coms in
        "GCC")
            clear
            PS3="Select which operating system to build for: "
            select sys in Windows Linux Quit
            do
                case $sys in
                "Windows")
                    clear
                    cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE="cmake/windows-amd64.cmake" -S "./" -B "out/build/GCC-ucrt64_amd64/"
                    cmake --build "./out/build/GCC-ucrt64_amd64/" --target StroopWafel
                    sleep 5
                    exit 1
                    break;;
                "Linux")
                    clear
                    cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE="cmake/linux-gcc-x86_64.cmake" -S "./" -B "/out/build/GCC-mingw64-amd64/"
                    cmake --build "./out/build/GCC-mingw64-amd64/" --target StroopWafel
                    sleep 5
                    exit 1
                    break;;
                "Quit")
                    break;;
                esac
                done;;

        "MSVC")
            clear
            cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE="cmake/windows-amd64.cmake" -G "Visual Studio 18 2026" -A x64 -S "./" -B "out/build/MSVC-2026_amd64"
            cmake --build "./out/build/MSVC-2026_amd64/" --target StroopWafel
            sleep 5
            exit 1
            break;;
        "Quit")
           break;;
        *)
           echo "Error";;
    esac
done
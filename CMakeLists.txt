cmake_minimum_required(VERSION 3.8)
project(alf_nes_tools)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES src/c_libs/charOps.c src/c_libs/charOps.h src/c_libs/chr.c src/c_libs/chr.h src/c_libs/cpu.c src/c_libs/cpu.h src/c_libs/instructions.c src/c_libs/instructions.h src/c_libs/ram.c src/c_libs/ram.h src/c_libs/romParser.c src/c_libs/romParser.h src/c_libs/instCallback.c src/c_libs/instCallback.h)
add_executable(alf_nes_tools ${SOURCE_FILES} src/main.c)
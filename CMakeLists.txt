# Min cmake version
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(VMT VERSION 0.1)

# Build origin
add_executable(VMT ./src/Main.c ./src/Utils.c ./src/Lexer.c)

# Use include folder
target_include_directories(VMT PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include")
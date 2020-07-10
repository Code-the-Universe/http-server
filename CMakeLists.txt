cmake_minimum_required(VERSION 3.16)
project(HTTP)


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Optimization flags
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# The C++ standard used
set(CMAKE_CXX_STANDARD 17)

# executable
add_executable(HTTP main.cpp src/Worker.cpp)

# compiler warnings
if(MSVC)
    target_compile_options(HTTP PRIVATE /W4 /WX)
else()
    target_compile_options(HTTP PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# need to link SFML before using

# finding SFML
find_package(SFML 2 COMPONENTS network system)

# linking
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(HTTP sfml-network sfml-system)

# include paths
target_include_directories(HTTP PRIVATE ${CMAKE_SOURCE_DIR}/include)

# needed for std::thread
find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
    target_compile_options(HTTP PUBLIC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
    target_link_libraries(HTTP "${CMAKE_THREAD_LIBS_INIT}")
endif()

# SFML-Demo - Copied out of SFML's GitHub repo

# add executable with source files
add_executable(socket SFML-Demo/Sockets.cpp SFML-Demo/UDP.cpp SFML-Demo/TCP.cpp)

# linking sfml for demos
target_link_libraries(socket sfml-network sfml-system)

cmake_minimum_required(VERSION 3.16)
project(HTTP)

# The C++ standard used
set(CMAKE_CXX_STANDARD 17)

# Compiler warning levels
add_executable(HTTP main.cpp)
if(MSVC)
    target_compile_options(HTTP PRIVATE /W4 /WX)
else()
    target_compile_options(HTTP PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# bin
set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# need to link SFML before using

# we're linking statically
set(SFML_STATIC_LIBRARIES TRUE)

# finding SFML
find_package(SFML COMPONENTS network system)

# linking
target_link_libraries(HTTP sfml-network sfml-system)


# needed for std::thread
find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
    target_compile_options(HTTP PUBLIC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
    target_link_libraries(HTTP "${CMAKE_THREAD_LIBS_INIT}")
endif()

# SFML-Demo - Copied out of SFML's GitHub repo

# set output dir
set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SFML-Demo/bin)

# add executable with source files
add_executable(socket SFML-Demo/Sockets.cpp SFML-Demo/UDP.cpp SFML-Demo/TCP.cpp)

# linking sfml for demos
target_link_libraries(socket sfml-network sfml-system)
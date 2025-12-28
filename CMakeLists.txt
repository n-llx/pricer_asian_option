cmake_minimum_required(VERSION 3.20)
project(pricer_asian_option VERSION 2.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Enable testing (Disabled for MVP build stability on legacy env)
# enable_testing()

add_subdirectory(src/Core)
add_subdirectory(src/CLI)
# add_subdirectory(src/Server)
# add_subdirectory(src/Tests)

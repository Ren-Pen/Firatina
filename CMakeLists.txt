cmake_minimum_required(VERSION 3.5.0)
project(FIRATINA VERSION 0.1.0 LANGUAGES C CXX)

set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 11)

include_directories("${PROJECT_SOURCE_DIR}/Framework/Common")
include_directories("${PROJECT_SOURCE_DIR}/Framework/Manager")
include_directories("${PROJECT_SOURCE_DIR}/Framework/Memory")
include_directories("${PROJECT_SOURCE_DIR}/Framework/Interface")

add_subdirectory(Framework)
add_subdirectory(Platform)
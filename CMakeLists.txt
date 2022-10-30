cmake_minimum_required(VERSION 3.18)
project(VOIP_Server)

set (SOURCE_DIR "src/")
file(GLOB SOURCES 
     "${SOURCE_DIR}*.c"
)
add_subdirectory(src)
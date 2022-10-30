set (INCLUDE_DIR "../include/")
set (CMAKE_BINARY_DIR "../../bin/")
include_directories(${INCLUDE_DIR})


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(voip_server ${SOURCES})
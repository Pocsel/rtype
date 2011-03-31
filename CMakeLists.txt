
# cmake -DCMAKE_CXX_COMPILER=clang++
#

cmake_minimum_required(VERSION 2.8)

# Modules supplémentaires
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

project(Rtype)

if (UNIX)
    set(CMAKE_CXX_CUSTOM_FLAGS "-Wall -Wextra -include stdint.h -include stdlib.h")
else(UNIX)
    set(CMAKE_CXX_CUSTOM_FLAGS "/FI\"windows/Types.hpp\" /FI\"stdlib.h\"")
    set(NETWORK_LIB "ws2_32")
endif(UNIX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_CUSTOM_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CMAKE_CXX_CUSTOM_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CMAKE_CXX_CUSTOM_FLAGS}")

file(GLOB common_src "common/*.[ch]pp")
include_directories(.)

add_subdirectory(terminal)
add_subdirectory(server)
add_subdirectory(server/games/chicken)
add_subdirectory(server/games/mainmenu)
add_subdirectory(server/games/bomberman)
add_subdirectory(server/games/rtype)
#add_subdirectory(server/games/blobby)



# Packages
#find_package(Threads)

# Sources
file(GLOB chicken_base_src
    )


if (UNIX)

else(UNIX)
    set(INCLUDE_DIR ../../../windows)
endif(UNIX)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${INCLUDE_DIR}
    ../common
    ../../logic
    ../../networkabstract
    ../../threadsabstract
    ../../console
    ../../games
    ../../../common
    ../../../b00st
    .)

list(APPEND
    chicken_src
    ${chicken_base_src}
    )
add_library(chicken SHARED
    ${chicken_src}
    )

set(LIBRARY_OUTPUT_PATH ..)

target_link_libraries(chicken
    ${CMAKE_THREAD_LIBS_INIT}
    ${MOAR_LIB}
    ${NETWORK_LIB}
    )

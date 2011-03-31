
# Packages
find_package(Qt4 COMPONENTS QtCore QtGui QtNetwork REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SFML REQUIRED Graphics Window System Audio)
find_package(Luabind REQUIRED)
find_package(Lua51 REQUIRED)


# Qt sources
file(GLOB terminal_qthpp "src/*.hpp")
file(GLOB terminal_qtforms "ui/*.ui")
file(GLOB terminal_qtres "ui/*.qrc")

# Others sources
file(GLOB terminal_base_src "src/*.[ch]pp")

include(${QT_USE_FILE})
include_directories(${CMAKE_CURRENT_BINARY_DIR}
                    ${OPENGL_INCLUDE_DIR}
                    ${GLEW_INCLUDE_DIR}
                    ${LUABIND_INCLUDE_DIR}
                    ${LUA_INCLUDE_DIR}
                    ../common
                    .)

qt4_wrap_cpp(terminal_src ${terminal_qthpp})
qt4_wrap_ui(terminal_src ${terminal_qtforms})
qt4_add_resources(terminal_src ${terminal_qtres})
add_definitions(${QT_DEFINITIONS})

list(APPEND
    terminal_src
        ${terminal_base_src}
        ${common_src}
)

add_executable(terminal
    ${terminal_src}
    ${terminal_qtres}
)

target_link_libraries(terminal
    ${QT_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARY}
    ${SFML_GRAPHICS_LIBRARY}
    ${SFML_WINDOW_LIBRARY}
    ${SFML_SYSTEM_LIBRARY}
    ${SFML_AUDIO_LIBRARY}
    ${LUA_LIBRARY}
    ${LUABIND_LIBRARY}
    )

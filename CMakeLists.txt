cmake_minimum_required(VERSION 3.19)
project(MusicApp LANGUAGES CXX)

# 1. Добавляем Network в список компонентов
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network)

qt_standard_project_setup()

qt_add_executable(MusicApp
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    musicapi.h musicapi.cpp
    songitem.h songitem.cpp
    config.h
    helperfunctions.h helperfunctions.cpp
    appexceptions.h appexceptions.cpp
)

# 2. Линкуем с Qt6::Network
target_link_libraries(MusicApp
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Network
)

install(TARGETS MusicApp
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET MusicApp
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
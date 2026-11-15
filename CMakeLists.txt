cmake_minimum_required(VERSION 3.19)
project(MusicApp LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network Test)

qt_standard_project_setup()

# --- Основное приложение ---
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
    artistitem.h artistitem.cpp
    radioitem.h radioitem.cpp
    albumitem.h albumitem.cpp
)

target_link_libraries(MusicApp
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Network
)

# --- Тесты (отдельная цель) ---
enable_testing()

qt_add_executable(MusicAppTests
    musicapitests.h musicapitests.cpp
    # Исходники, которые тестируем, — компилируются ещё раз в тестовую цель
    musicapi.h musicapi.cpp
    songitem.h songitem.cpp
    helperfunctions.h helperfunctions.cpp
    appexceptions.h appexceptions.cpp
    artistitem.h artistitem.cpp
    radioitem.h radioitem.cpp
    albumitem.h albumitem.cpp
    config.h
)

target_link_libraries(MusicAppTests
    PRIVATE
        Qt6::Core
        Qt6::Network
        Qt6::Test
)

add_test(NAME MusicAppTests COMMAND MusicAppTests)

# --- Установка (только приложение) ---
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
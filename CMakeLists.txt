cmake_minimum_required(VERSION 3.19)
project(MusicApp LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network Multimedia)

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
    collectionitem.h collectionitem.cpp
    musicitem.h musicitem.cpp
    userdataloader.h
    userdataloader.cpp
    paths.h
    player.h player.cpp
    networkbypass.h networkbypass.cpp
    playercontrol.h playercontrol.cpp
    userdatamanager.h userdatamanager.cpp
)

# --- BASS: линкуемся прямо на 64-битную DLL ---
set(BASS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/bass")
target_include_directories(MusicApp PRIVATE ${BASS_DIR})
target_link_libraries(MusicApp PRIVATE ${BASS_DIR}/bass.dll)

# --- Qt-библиотеки ---
target_link_libraries(MusicApp
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Network
        Qt6::Multimedia
)

# --- Копирование DLL BASS в папку сборки ---
add_custom_command(TARGET MusicApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${BASS_DIR}/bass.dll"
        "$<TARGET_FILE_DIR:MusicApp>/bass.dll"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${BASS_DIR}/bass_aac.dll"
        "$<TARGET_FILE_DIR:MusicApp>/bass_aac.dll"
    COMMENT "Copying BASS DLLs to output directory"
)

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
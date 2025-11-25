cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 23)
project(sem3lab2 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Multimedia)

qt_standard_project_setup()

qt_add_executable(sem3lab2
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.h mainwindow.cpp mainwindow.ui

    TimerAppResources.qrc
    addwindow.h addwindow.cpp addwindow.ui
    alarmswindow.h alarmswindow.cpp alarmswindow.ui
    timerswindow.h timerswindow.cpp timerswindow.ui

    timer.h timer.cpp

)

target_link_libraries(sem3lab2 PRIVATE Qt6::Core Qt6::Widgets Qt6::Multimedia)

include(GNUInstallDirs)

install(TARGETS sem3lab2
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET sem3lab2
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

cmake_minimum_required(VERSION 3.24)
project(App1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.5.2/mingw_64/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Sql
        Network
        REQUIRED)

add_executable(App1 main.cpp
        Presentation/AuthWidgets/LoginWidget.cpp
        Presentation/AuthWidgets/LoginWidget.h
        Presentation/AuthWidgets/LoginWidget.ui
        Presentation/MainWindow.cpp
        Presentation/MainWindow.h
        Presentation/MainWindow.ui
        Domain/Task.cpp
        Domain/Task.h
        Presentation/MainWidget.cpp
        Presentation/MainWidget.h
        Presentation/MainWidget.ui
        Service/ServiceApp.cpp
        Service/ServiceApp.h
        Presentation/ListModels/MyFirstModel.cpp
        Presentation/ListModels/MyFirstModel.h
        Presentation/ListModels/MySecondModel.cpp
        Presentation/ListModels/MySecondModel.h
        Presentation/TasksWidgets/AddTaskWidget.cpp
        Presentation/TasksWidgets/AddTaskWidget.h
        Presentation/TasksWidgets/AddTaskWidget.ui
        Service/ServiceAuth.cpp
        Service/ServiceAuth.h
        Repository/RepositoryApp.cpp
        Repository/RepositoryApp.h
        Observer/ObserverAuth.cpp
        Observer/ObserverAuth.h
        Presentation/AuthWidgets/RegisterWidget.cpp
        Presentation/AuthWidgets/RegisterWidget.h
        Presentation/AuthWidgets/RegisterWidget.ui
        Observer/ObservableAuth.cpp
        Observer/ObservableAuth.h
        Observer/ObserverApp.cpp
        Observer/ObserverApp.h
        Observer/ObservableApp.cpp
        Observer/ObservableApp.h
        Presentation/TasksWidgets/ViewTaskWidget.cpp
        Presentation/TasksWidgets/ViewTaskWidget.h
        Presentation/TasksWidgets/ViewTaskWidget.ui
        Presentation/ListsWidgets/ListObject.cpp
        Presentation/ListsWidgets/ListObject.h
        Presentation/ListsWidgets/ListObject.ui
)
target_link_libraries(App1
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Sql
        Qt::Network
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()

set(app_resource_files
        "Icons/"
)

qt_add_resources(App1 "App1"
    PREFIX
        "/"
        FILES
        ${app_resource_files}
)

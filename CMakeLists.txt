cmake_minimum_required(VERSION 3.5)

project(cryptoview LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt5 COMPONENTS Widgets WebSockets REQUIRED)

add_executable(cryptoview
    main.cpp
    mainwindow.cpp
    mainwindow.hpp
    tiingoconnection.cpp
    tiingoconnection.hpp
    mainwindow.ui
  )


target_link_libraries(cryptoview PRIVATE Qt5::Widgets Qt5::WebSockets)

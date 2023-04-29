cmake_minimum_required(VERSION 3.16)

project(Calculator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

add_executable(Calculator
    src/main.cpp
    src/backend.h src/backend.cpp
    src/settings.h src/settings.cpp

    qml/qml.qrc

    README.md
)

target_compile_definitions(Calculator
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(Calculator
    PRIVATE Qt6::Quick)

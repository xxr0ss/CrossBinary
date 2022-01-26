cmake_minimum_required(VERSION 3.5)

project(CrossBinary VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(INCLUDE_ROOT_DIR "${CMAKE_SOURCE_DIR}/include")

configure_file("${CMAKE_SOURCE_DIR}/config.h.in" "${INCLUDE_ROOT_DIR}/config.h")

include_directories(${INCLUDE_ROOT_DIR} "${INCLUDE_ROOT_DIR}/ui")

FILE(GLOB HEADER_FILES "${INCLUDE_ROOT_DIR}/*.h" "${INCLUDE_ROOT_DIR}/ui/*.h")
FILE(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.c" "${CMAKE_SOURCE_DIR}/src/*.cpp")
FILE(GLOB UI_FILES "${CMAKE_SOURCE_DIR}/src/UI/*.ui")

set(PROJECT_SOURCES
        ${HEADER_FILES}
        ${SRC_FILES}
        ${UI_FILES}
)

qt_add_executable(CrossBinary
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(CrossBinary PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


qt_finalize_executable(CrossBinary)

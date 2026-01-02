#
# Copyright (C) 2020-2026 QuasarApp.
# Distributed under the GPLv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.19)
project(qTbot LANGUAGES CXX)
if(TARGET ${PROJECT_NAME})
  message("The ${PROJECT_NAME} arledy included in main Project")
  return()
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (ANDROID OR WIN32)
    set(BUILD_SHARED_LIBS ON)
endif()

find_package(Qt6 COMPONENTS Core Network REQUIRED)
find_package(Qt6 COMPONENTS Test QUIET)

include(submodules/CMake/QuasarApp.cmake)

updateGitVars()
set(QTBOT_VERSION "0.2.${GIT_COMMIT_COUNT}.${GIT_COMMIT_HASH}")
set(QTBOT_PACKAGE_ID "quasarapp.core.qTbot")

option(QTBOT_TESTS "This option disables or enables tests of the ${PROJECT_NAME} project"  ON)
option(QTBOT_EXAMPLE "This option disables or enables example app of the ${PROJECT_NAME} project" ON)
option(QTBOT_PRINT_RQUESTS "This option disables or enables printing requests" OFF)
option(QTBOT_PRINT_ERRORS "This option disables or enables printing errors" ON)

if (ANDROID OR IOS OR QA_WASM32)
    set(QTBOT_TESTS OFF CACHE BOOL "This option force disbled for ANDROID IOS QA_WASM32 and Not Qt projects" FORCE)
    set(QTBOT_EXAMPLE OFF CACHE BOOL "This option force disbled for ANDROID IOS QA_WASM32 and Not Qt projects" FORCE)

endif()

make_directory(Distro)

initAll()

add_subdirectory(src/qTbot)

if (QTBOT_EXAMPLE)
    add_subdirectory(src/example)
endif()

if (QTBOT_TESTS)
    add_subdirectory(tests)
else()
    message("The ${PROJECT_NAME} tests is disabled.")
endif()

configure_file_in(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf)
addDoc(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf)

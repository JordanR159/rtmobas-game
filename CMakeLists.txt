cmake_minimum_required(VERSION 3.10)
project(rtmobas-game)

set(CMAKE_CXX_STANDARD 17)

file(GLOB RTMOBAS_HEADERS "headers/*.hpp" "headers/*.h" "glm/*.hpp")
file(GLOB RTMOBAS_SRC "src/*.cpp" "src/*.c" "src/*/*.cpp" "src/*/*.c")
add_executable(rtmobas-game rpmalloc/rpmalloc.h rpmalloc/rpmalloc.c rpmalloc/malloc.c ${RTMOBAS_HEADERS} ${RTMOBAS_SRC})

include_directories(headers)
include_directories(rpmalloc)
include_directories(glm)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
set(SFML_ROOT "${CMAKE_SOURCE_DIR}/SFML")

find_package(SFML REQUIRED graphics system window audio)
if(SFML_FOUND)
    message(STATUS "${CMAKE_CURRENT_LIST_DIR} ${SFML_INCLUDE_DIR}")
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(rtmobas-game ${SFML_LIBRARIES})
endif()

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DIS_UNIX")
    target_link_libraries(rtmobas-game pthread dl)
endif(UNIX)


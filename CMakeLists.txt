cmake_minimum_required(VERSION 3.10)
project(rtmobas-game)

set(CMAKE_CXX_STANDARD 17)

file(GLOB RTMOBAS_HEADERS "headers/*.hpp" "headers/*.h")
file(GLOB RTMOBAS_SRC "src/*.cpp" "src/*.c")
add_executable(rtmobas-game rpmalloc/rpmalloc.h rpmalloc/rpmalloc.c ${RTMOBAS_HEADERS} ${RTMOBAS_SRC})

include_directories(headers)
include_directories(rpmalloc)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED graphics system window audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(rtmobas-game ${SFML_LIBRARIES})
endif()


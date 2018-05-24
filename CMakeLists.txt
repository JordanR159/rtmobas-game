cmake_minimum_required(VERSION 3.10)
project(rtmobas-game)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp)
add_executable(rtmobas-game ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED graphics system window audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(rtmobas-game ${SFML_LIBRARIES})
endif()


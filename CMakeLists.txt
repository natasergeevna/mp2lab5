cmake_minimum_required(VERSION 2.8) #Проверка версии CMake.

set (CMAKE_CXX_STANDARD 11)
set(PROJECT_NAME mp2-lab12-text)
project(${PROJECT_NAME})

set(StackLib StackLib) 
set(TextLib TextLib)
set(main main)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/TextLib ${CMAKE_CURRENT_SOURCE_DIR}/StackLib) 

add_subdirectory(TextLib)
add_subdirectory(StackLib)
add_subdirectory(main)

add_subdirectory(gtest)
add_subdirectory(test)

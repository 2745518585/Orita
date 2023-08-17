cmake_minimum_required(VERSION 3.15)
add_definitions(-w)
add_subdirectory(include)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

project(chdata)
add_executable(chdata source/chdata.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

project(check)
add_executable(check source/check.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

project(compile)
add_executable(compile source/compile.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

project(judge)
add_executable(judge source/judge.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

project(run)
add_executable(run source/run.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

project(setfile)
add_executable(setfile source/setfile.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

project(orita VERSION 0.1.4)
configure_file(Oritaconfig.hpp.in Oritaconfig.hpp)
add_executable(orita source/orita.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/include)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    file(WRITE "$ENV{APPDATA}\\Orita\\path.txt" ${CMAKE_BINARY_DIR})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    file(WRITE "$ENV{HOME}/.Orita/path.txt" ${CMAKE_BINARY_DIR})
endif()
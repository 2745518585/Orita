cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR})

add_subdirectory(include)
add_subdirectory(poco)

project(chdata)
add_executable(chdata source/chdata.cpp)
target_link_libraries(chdata Poco::Foundation Poco::Net Poco::Util)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

project(check)
add_executable(check source/check.cpp)
target_link_libraries(check Poco::Foundation Poco::Net Poco::Util)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

project(config)
add_executable(config source/config.cpp)
target_link_libraries(config Poco::Foundation Poco::Net Poco::Util)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

project(compile)
add_executable(compile source/compile.cpp)
target_link_libraries(compile Poco::Foundation Poco::Net Poco::Util)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

project(judge)
add_executable(judge source/judge.cpp)
target_link_libraries(judge Poco::Foundation Poco::Net Poco::Util)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

project(run)
add_executable(run source/run.cpp)
target_link_libraries(run Poco::Foundation Poco::Net Poco::Util)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

project(orita VERSION 0.2.0)
configure_file(Oritaconfig.hpp.in Oritaconfig.hpp)
add_executable(orita source/orita.cpp)
target_link_libraries(orita Poco::Foundation Poco::Net Poco::Util)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/include)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    file(WRITE "$ENV{APPDATA}\\Orita\\path.txt" ${CMAKE_BINARY_DIR})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    file(WRITE "$ENV{HOME}/.Orita/path.txt" ${CMAKE_BINARY_DIR})
endif()
cmake_minimum_required(VERSION 3.15)
add_subdirectory(include)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(CHANGNA)
add_executable(CHANGNA source/changna.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

project(CHDATA)
add_executable(CHDATA source/chdata.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

project(CHECK)
add_executable(CHECK source/check.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

project(CMP)
add_executable(CMP source/cmp.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

project(COMPILE)
add_executable(COMPILE source/compile.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

project(JUDGE)
add_executable(JUDGE source/judge.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

project(RESET_ORITA)
add_executable(RESET_ORITA source/reset_orita.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

project(RUN)
add_executable(RUN source/run.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

project(SETFILE)
add_executable(SETFILE source/setfile.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

project(ORITA VERSION 0.0.12)
configure_file(Oritaconfig.hpp.in Oritaconfig.hpp)
add_executable(ORITA source/orita.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/include)

cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)

project(orita VERSION 0.2.3)
configure_file(Oritaconfig.hpp.in Oritaconfig.hpp)

file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

configure_file("orita.hpp" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} COPYONLY)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(os_name "windows")
    configure_file("path.bat" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} COPYONLY)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(os_name "linux")
    configure_file("path.sh" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} COPYONLY)
endif()

set(files_dir ${CMAKE_SOURCE_DIR}/files/${os_name})
file(GLOB_RECURSE files_list ${files_dir}/*)
foreach(file ${files_list})
    file(RELATIVE_PATH relative_path ${files_dir} ${file})
    set(dest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/files/${relative_path})
    configure_file(${file} ${dest} COPYONLY)
endforeach()

add_subdirectory(include)
add_subdirectory(nlohmann)
add_subdirectory(poco)
add_subdirectory(spdlog)
add_subdirectory(termcolor)

add_executable(main source/orita.cpp)
target_link_libraries(main Poco::Foundation Poco::Util nlohmann_json::nlohmann_json spdlog::spdlog termcolor::termcolor)
target_include_directories(main PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/include)

add_executable(orita orita.cpp)
set_target_properties(orita PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/bin)
set_target_properties(orita PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/bin)
set_target_properties(orita PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/bin)

add_dependencies(orita main)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    file(WRITE "$ENV{APPDATA}\\Orita\\path.txt" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    file(WRITE "$ENV{HOME}/.Orita/path.txt" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()

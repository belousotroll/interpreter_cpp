cmake_minimum_required(VERSION 3.24)
project(interpreter_cpp)

set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME}
        main.cpp)

target_include_directories(
        ${PROJECT_NAME} PUBLIC
        ${CMAKE_HOME_DIRECTORY}/include
)
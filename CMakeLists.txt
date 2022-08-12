# set the minimum version
cmake_minimum_required(VERSION 3.2)

# set project name
project(Regx)

# set main.cpp
set(source src/main.cpp)

add_executable(${PROJECT_NAME} ${source})


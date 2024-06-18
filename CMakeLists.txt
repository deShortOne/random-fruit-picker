cmake_minimum_required(VERSION 3.22.1)
project(Random_Fruits)

include_directories(include)

add_executable(${PROJECT_NAME} src/main.cpp src/fruitPicker.cpp src/fruit.cpp)

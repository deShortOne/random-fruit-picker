cmake_minimum_required(VERSION 3.22.1)
project(Random_Fruits)

add_executable(${PROJECT_NAME} 
    src/main.cpp 
    src/fruitPicker.cpp 
    src/fruit.cpp
)

add_subdirectory(lib/cxxopts)

target_include_directories(${PROJECT_NAME} 
    PUBLIC include/
    PUBLIC lib/cxxopts/include
)

target_link_directories(${PROJECT_NAME}
    PRIVATE lib/cxxopts/src
)

target_link_libraries(${PROJECT_NAME}
    cxxopts
)

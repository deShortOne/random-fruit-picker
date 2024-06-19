cmake_minimum_required(VERSION 3.22.1)
project(Random_Fruits)

add_executable(${PROJECT_NAME} 
    src/main.cpp 
    src/fruitPicker.cpp 
    src/fruit.cpp
)

# DOWNLOAD ALL SUBMODULES
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule updated")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_SUBMOD_RESULT
        )
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        message(FATAL_ERROR "The command 'git submodule update --init --recursive' failed with ${GIT_SUBMOD_RESULT}, please checkout any existing submodules")
        endif()
    endif()
endif()

# CHECK ALL SUBMODULES
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/lib/cxxopts/CMakeLists.txt")
    message(FATAL_ERROR "The cxxopts submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

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

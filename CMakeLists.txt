# Cmake version
cmake_minimum_required (VERSION 3.8)

# Name
project(Genetic_Algorithm)

# At least c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# OpenGL
cmake_policy(SET CMP0072 NEW)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

# Add sources to this project's executable.
file(GLOB_RECURSE sources src/*.cpp header/*.h)
add_executable (Genetic_Algorithm ${sources})

# static linking
target_link_libraries(Genetic_Algorithm PRIVATE -lm -lglut -lGL -lGLU)

# library include
target_include_directories (Genetic_Algorithm PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/header/)

# Debug preprocessor definition
target_compile_definitions(Genetic_Algorithm PUBLIC "$<$<CONFIG:Debug>:_DEBUG>")

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/data)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/plots)

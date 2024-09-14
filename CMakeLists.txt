cmake_minimum_required(VERSION 3.30)
project(IM_BMI CXX)
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-Wall -O2 -g")

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(include include/imgui/ include/glad/)


file(GLOB IMGUI_FILES "lib/imgui/*.cpp")
set(SOURCES src/main.cpp src/glad.c)

add_executable(IM_BMI ${SOURCES} ${IMGUI_FILES})
target_link_libraries(IM_BMI PRIVATE ${OPENGL_LIBRARIES} glfw)

cmake_minimum_required(VERSION 3.1.0)

project (ray-tracing-in-one-weekend-cpp)

set ( CMAKE_CXX_STANDARD 11 )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

set (SRC_FILES
	src/camera.h
	src/color.h
	src/common.h
	src/hittable.h
	src/hittable_list.h
	src/material.h
	src/ray.h
	src/sphere.h
	src/vec3.h
	src/main.cpp
)

add_executable(ray-tracing-in-one-weekend-cpp ${SRC_FILES})
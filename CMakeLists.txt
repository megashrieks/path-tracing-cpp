cmake_minimum_required(VERSION 3.13)

project(PATHTRACER)


# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_PARALLEL_LEVELS 4)

file(GLOB CPP_SOURCE
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*/*.cpp"
)
file(GLOB INCLUDE_FILES
    "${PROJECT_SOURCE_DIR}/include/*.*"
    "${PROJECT_SOURCE_DIR}/include/*/*.*"
)
file(GLOB INCLUDE_DIRS
    "${PROJECT_SOURCE_DIR}/include/*"
)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${INCLUDE_DIRS})
add_executable(main ${CPP_SOURCE} ${INCLUDE_FILES}) 
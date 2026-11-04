
cmake_minimum_required(VERSION 3.10)

project(version_homework)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(OpenCV REQUIRED)
find_package(fmt CONFIG REQUIRED)

add_executable(version_homework
    main_640*640.cpp
    tools.cpp
)

target_include_directories(version_homework PRIVATE
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(version_homework PRIVATE
    ${OpenCV_LIBS}
    fmt::fmt
)



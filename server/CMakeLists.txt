cmake_minimum_required(VERSION 3.15)
project(server)
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(server ${SRC})

# 头文件搜索路径
include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

# Link necessary libraries
target_link_libraries(server pthread mysqlclient jsoncpp)



cmake_minimum_required(VERSION 2.8)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
project(zRenderer)

aux_source_directory(./code/src SRC)
aux_source_directory(./code/include INC)
include_directories(/usr/local/include ./code/include)

add_executable(${PROJECT_NAME} ${SRC} ./code/main.cpp)

target_link_libraries(${PROJECT_NAME}
    -lpthread
    -lassimp
    )

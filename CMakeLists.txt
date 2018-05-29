cmake_minimum_required(VERSION 3.10)
project(pandia)

set(CMAKE_CXX_STANDARD 14)


include(conanbuildinfo.cmake)
CONAN_BASIC_SETUP()

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
        PRIVATE ${CONAN_LIBS}
        )

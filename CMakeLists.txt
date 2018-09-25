cmake_minimum_required(VERSION 3.10)
project(pandia)

set(CMAKE_CXX_STANDARD 14)


include(conanbuildinfo.cmake)
CONAN_BASIC_SETUP()


set(DOCOPT_SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/docopt/docopt.cpp
        ${CMAKE_SOURCE_DIR}/docopt/docopt.h
        ${CMAKE_SOURCE_DIR}/docopt/docopt_private.h
        ${CMAKE_SOURCE_DIR}/docopt/docopt_util.h
        ${CMAKE_SOURCE_DIR}/docopt/docopt_value.h
        )

add_executable(${PROJECT_NAME} main.cpp ${DOCOPT_SOURCE_FILES})


target_link_libraries(${PROJECT_NAME}
        PRIVATE ${CONAN_LIBS}
        )

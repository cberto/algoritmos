cmake_minimum_required(VERSION 3.16)
project(TP_INTEGRADOR LANGUAGES CXX)

add_executable(tp_integrador
    src/main.cpp
    src/Sistema.cpp
)

target_include_directories(tp_integrador PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
set_target_properties(tp_integrador PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

if(MSVC)
    target_compile_options(tp_integrador PRIVATE /W4 /utf-8)
else()
    target_compile_options(tp_integrador PRIVATE -Wall -Wextra -Wpedantic)
endif()

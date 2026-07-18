cmake_minimum_required(VERSION 3.20)

project(pytest_unity_example LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_library(example STATIC
    src/math_utils.c
    src/ring_buffer.c
)

target_include_directories(example
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(example
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

# Supply Unity from outside the project:
#
# cmake -S . -B build -G Ninja -DUNITY_ROOT=../../vendor/unity
set(UNITY_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../vendor/unity")
cmake_path(ABSOLUTE_PATH UNITY_ROOT NORMALIZE)

if(DEFINED UNITY_ROOT)
    add_library(unity STATIC
        ${UNITY_ROOT}/src/unity.c
    )

    target_include_directories(unity
        PUBLIC
            ${UNITY_ROOT}/src
    )

    file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.c")

    foreach(test_source IN LISTS TEST_SOURCES)
        get_filename_component(test_name ${test_source} NAME_WE)

        set(test_runner_source ${CMAKE_CURRENT_BINARY_DIR}/${test_name}_runner.c)

        add_custom_command(
            OUTPUT ${test_runner_source}
            COMMAND ruby ${UNITY_ROOT}/auto/generate_test_runner.rb ${test_source} ${test_runner_source}
            DEPENDS ${test_source}
        )

        add_executable(${test_name} ${test_source} ${test_runner_source})
        target_link_libraries(${test_name} PRIVATE example unity)
    endforeach()
else()
    message(WARNING "Unity submodule not cloned.ß Skipping test build.")
endif()

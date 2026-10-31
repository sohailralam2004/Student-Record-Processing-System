cmake_minimum_required(VERSION 3.15)

project(StudentRecordProcessingSystem VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(student_person Person.cpp)
target_include_directories(student_person PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(student_person PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-pedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

add_library(student_manager StudentManager.cpp)
target_link_libraries(student_manager PUBLIC student_person)
target_include_directories(student_manager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(student_manager PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-pedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

add_library(student_generator StudentFileGenerator.cpp)
target_include_directories(student_generator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(student_generator PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-pedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

add_executable(students main.cpp)
target_link_libraries(students PRIVATE student_manager)

add_executable(processor processor_main.cpp)
target_link_libraries(processor PRIVATE student_manager)

add_executable(generate_students generator_main.cpp)
target_link_libraries(generate_students PRIVATE student_generator)

add_executable(container_benchmark container_benchmark.cpp)
target_link_libraries(container_benchmark PRIVATE student_person)

target_compile_options(container_benchmark PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-pedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

add_executable(strategy_benchmark strategy_benchmark.cpp)
target_link_libraries(strategy_benchmark PRIVATE student_person)

target_compile_options(strategy_benchmark PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-pedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

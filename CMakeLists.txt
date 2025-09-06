set(PROJECT "bootdev")

cmake_minimum_required(VERSION 3.16)
project(${PROJECT} C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Og -g -pg")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------------------------------
# Library µnit

file(GLOB_RECURSE LIBRARY_SOURCES "vendor/munit/*.c")

add_library(munit ${LIBRARY_SOURCES})

# ------------------------------------------
# Executable

file(GLOB LESSONS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

set(ALL_RUN "")
set(ALL_TARGETS "")
foreach(LESSON ${LESSONS})
    if(NOT IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${LESSON})
        continue()
    endif()

    file(GLOB LESSON_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${LESSON}/*.c)
    if(NOT LESSON_SOURCES)
        continue()
    endif()
    list(APPEND LESSON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/bootlib.c)

    # Get last directory name of the path to use as exe
    get_filename_component(EXE_NAME ${LESSON} NAME)

    add_executable(${EXE_NAME} ${LESSON_SOURCES})
    target_include_directories(${EXE_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/${LESSON})
    target_link_libraries(${EXE_NAME} munit)

    # Collect all the directory names for the run target
    list(APPEND ALL_RUN COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXE_NAME})
    list(APPEND ALL_TARGETS ${EXE_NAME})
endforeach()

# ------------------------------------------
# Execute target

add_custom_target(run
    ${ALL_RUN})

foreach(target ${ALL_TARGETS})
	add_dependencies(run ${target})
endforeach()

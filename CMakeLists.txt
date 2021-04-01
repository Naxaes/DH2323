cmake_minimum_required(VERSION 3.7)
project(DH2323)

# ---- Setting up useful compiler flags ----
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(STATUS "Building for Clang")
    set(COMPILER_FLAGS      "-pedantic -pedantic-errors")
    set(COMPILER_FLAGS_SLOW "-O0 -g -fsanitize=address -fno-omit-frame-pointer")
    set(COMPILER_FLAGS_FAST "-O2")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # Using Visual Studio C++
    message(STATUS "Building for MSVC")
    set(COMPILER_FLAGS      "-W4 -D_CRT_SECURE_NO_WARNINGS -Oi -EHa")
    set(COMPILER_FLAGS_SLOW "-Od -Zi")
    set(COMPILER_FLAGS_FAST "-O2")
else()
    message(STATUS "Building for unknown compiler; will not add any flags.")
endif()


if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(COMPILER_FLAGS "${COMPILER_FLAGS} ${COMPILER_FLAGS_SLOW}")
    message(STATUS "Building debug...")
else()
    set(COMPILER_FLAGS "${COMPILER_FLAGS} ${COMPILER_FLAGS_FAST}")
    message(STATUS "Building release...")
endif()


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS  "${COMPILER_FLAGS}")


# ---- Setting paths and targets ----
set(SDL2_PATH libraries/SDL2-2.0.14)
set(GLM_PATH  libraries/glm-0.9.9.8)
set(TEST_PATH libraries/test)
set(HELP_PATH libraries/)


add_subdirectory(${SDL2_PATH} EXCLUDE_FROM_ALL)
set_target_properties(SDL2 PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)


add_executable(Lab1 Lab1/main.cpp)                     # Add source files for lab 1.
target_link_libraries(Lab1 PRIVATE SDL2)               # Link SDL2.
target_include_directories(Lab1 PRIVATE ${HELP_PATH})  # Add our helper headers.
target_include_directories(Lab1 PRIVATE ${GLM_PATH})   # Add GLM header library.
target_include_directories(Lab1 PRIVATE ${SDL2_PATH})  # Add SDL2 headers.
target_compile_definitions(Lab1 PRIVATE SCREENSHOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Lab1/screenshots/")  # Set path for screenshots.


add_executable(Lab2 Lab2/main.cpp)                     # Add source files for lab 2.
target_link_libraries(Lab2 PRIVATE SDL2)               # Link SDL2.
target_include_directories(Lab2 PRIVATE ${HELP_PATH})  # Add our helper headers.
target_include_directories(Lab2 PRIVATE ${GLM_PATH})   # Add GLM header library.
target_include_directories(Lab2 PRIVATE ${SDL2_PATH})  # Add SDL2 headers.
target_compile_definitions(Lab2 PRIVATE SCREENSHOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Lab2/screenshots/")  # Set path for screenshots.


add_executable(Lab3 Lab3/main.cpp)                     # Add source files for lab 3.
target_link_libraries(Lab3 PRIVATE SDL2)               # Link SDL2.
target_include_directories(Lab3 PRIVATE ${HELP_PATH})  # Add our helper headers.
target_include_directories(Lab3 PRIVATE ${GLM_PATH})   # Add GLM header library.
target_include_directories(Lab3 PRIVATE ${SDL2_PATH})  # Add SDL2 headers.
target_compile_definitions(Lab3 PRIVATE SCREENSHOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Lab3/screenshots/")  # Set path for screenshots.


# On Windows, we want to copy the .dll file 
# to the same folder as the executables.
if (WIN32)
    add_custom_command(
        TARGET Lab1 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_FILE_DIR:SDL2>
        $<TARGET_FILE_DIR:Lab1>
    )
     add_custom_command(
        TARGET Lab2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_FILE_DIR:SDL2>
        $<TARGET_FILE_DIR:Lab1>
    )
    add_custom_command(
        TARGET Lab3 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_FILE_DIR:SDL2>
        $<TARGET_FILE_DIR:Lab1>
    )
endif()


# ---- Add tests ----
set(TESTS test1 other)  # Add the name of the files in `test/` separated with space.

FOREACH(test ${TESTS})
    add_executable(${test} tests/${test}.cpp)                 # Add source file.
    target_link_libraries(${test} PRIVATE SDL2)               # Link SDL2.
    target_include_directories(${test} PRIVATE ${HELP_PATH})  # Add our helper headers.
    target_include_directories(${test} PRIVATE ${GLM_PATH})   # Add GLM header library.
    target_include_directories(${test} PRIVATE ${SDL2_PATH})  # Add SDL2 headers.
    target_include_directories(${test} PRIVATE ${TEST_PATH})  # Add test headers.
ENDFOREACH()
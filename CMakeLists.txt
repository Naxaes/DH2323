cmake_minimum_required(VERSION 3.7)
project(DH2323)


set(SDL2_PATH libraries/SDL2-2.0.14)
set(GLM_PATH  libraries/glm-0.9.9.8)
set(HELP_PATH libraries/)


add_subdirectory(${SDL2_PATH} EXCLUDE_FROM_ALL)


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

    # Remove warnings of unsafe C methods.
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

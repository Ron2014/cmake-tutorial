cmake_minimum_required(VERSION 3.10)

# cmake_minimum_required: https://cmake.org/cmake/help/v3.16/command/cmake_minimum_required.html?highlight=cmake_minimum_required
# CMake version = 3.10

# set the project name and version
project(Tutorial VERSION 1.0)

# project: https://cmake.org/cmake/help/v3.16/command/project.html#command:project
# we have:
# PROJECT_NAME CMAKE_PROJECT_NAME
# PROJECT_SOURCE_DIR PROJECT_BINARY_DIR
# Tutorial_SOURCE_DIR Tutorial_BINARY_DIR
# PROJECT_VERSION_MAJOR, Tutorial_VERSION_MAJOR = 1
# PROJECT_VERSION_MINOR, Tutorial_VERSION_MINOR = 0
# PROJECT_VERSION, Tutorial_VERSION
# CMAKE_PROJECT_VERSION 

message("PROJECT_NAME = ${PROJECT_NAME}")
message("CMAKE_PROJECT_NAME = ${CMAKE_PROJECT_NAME}")
message("PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
message("Tutorial_SOURCE_DIR = ${Tutorial_SOURCE_DIR}")
message("Tutorial_BINARY_DIR = ${Tutorial_BINARY_DIR}")
message("PROJECT_VERSION_MAJOR = ${PROJECT_VERSION_MAJOR}")
message("PROJECT_VERSION_MINOR = ${PROJECT_VERSION_MINOR}")
message("PROJECT_VERSION = ${PROJECT_VERSION}")
message("Tutorial_VERSION = ${Tutorial_VERSION}")
message("CMAKE_PROJECT_VERSION = ${CMAKE_PROJECT_VERSION}")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(Tutorial tutorial.cxx)

configure_file(TutorialConfig.h.in TutorialConfig.h)

# configure_file: https://cmake.org/cmake/help/v3.16/command/configure_file.html?highlight=configure_file
# 1. copy file: source_dir -> binary_dir
# 2. substitute variable values referenced (@VAR@ or ${VAR})
# 3. #cmakedefine VAR       -> #define VAR
#    #cmakedefine01 VAR     -> #define VAR 1
#
# @ONLY
# Restrict variable replacement to references of the form @VAR@. This is useful for configuring scripts that use ${VAR} syntax.

message("====== before include")
message("INCLUDE_DIRECTORIES = ${INCLUDE_DIRECTORIES}")
message("INTERFACE_INCLUDE_DIRECTORIES = ${INTERFACE_INCLUDE_DIRECTORIES}")

target_include_directories(Tutorial PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

# PROJECT_BINARY_DIR: https://cmake.org/cmake/help/v3.16/variable/PROJECT_BINARY_DIR.html?highlight=project_binary_dir#project-binary-dir
# target_include_directories: https://cmake.org/cmake/help/v3.16/command/target_include_directories.html?highlight=target_include_directories
# Tutorial comes from add_executable above
# PUBLIC make dir "${PROJECT_BINARY_DIR}" append into INCLUDE_DIRECTORIES or INTERFACE_INCLUDE_DIRECTORIES
#
# INCLUDE_DIRECTORIES: for exe & libary target
# List of preprocessor include file search directories.
# 
# INTERFACE_INCLUDE_DIRECTORIES: for library & interface(only header files) target
# List of public include directories requirements for a library.


# target_include_directories: https://cmake.org/cmake/help/v3.16/command/target_include_directories.html?highlight=target_include_directories
# Tutorial comes from add_executable above
# PUBLIC make dir "${PROJECT_BINARY_DIR}" append into INCLUDE_DIRECTORIES property or INTERFACE_INCLUDE_DIRECTORIES property

message("====== after include")
message("INCLUDE_DIRECTORIES = ${INCLUDE_DIRECTORIES}")
message("INTERFACE_INCLUDE_DIRECTORIES = ${INTERFACE_INCLUDE_DIRECTORIES}")

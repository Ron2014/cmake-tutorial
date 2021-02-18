cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Tutorial VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# should we use our own math functions
# option(USE_MYMATH "Use tutorial provided math implementation" ON)
#
# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
#
# archieve output artifacts:
# 1. static library file    (.lib .a)       of a static library target    created by add_library() with STATIC option.
# 2. import library file    (.lib)          of a shared library target    created by add_library() with SHARED option.
# 3. import library file    (.lib)          of an executable target       created by add_executable() when seted ENABLE_EXPORTS.
# 4. linker import file     (.imp)          of an executable target       created by add_executable() when seted ENABLE_EXPORTS.
#
# library output artifacts:
# 1. loadable module file   (.dll .so)      of a module target            created by add_library() with MODULE option.
# 2. shared library file    (.so .dylib)    of a shared library target    created by add_library() with SHARED option.
#
# runtime output artifacts:
# 1. executable file        (.exe)          of an executable target       created by add_executable()
# 2. executable file        (.dll)          of a shared library target    created by add_library() with SHARED option.

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(TutorialConfig.h.in TutorialConfig.h)

# add the MathFunctions library
# if(USE_MYMATH)
#   add_subdirectory(MathFunctions)
#   list(APPEND EXTRA_LIBS MathFunctions)
# endif()

# old struction
# 
# -- Tutorial: exe
# ---- TutorialConfig.h
# ---- Tutorial.cxx
# ---- if USE_MYMATH
# ------ MathFunctions.h
# ------ MathFunctions: lib
# -------- Table.h
# -------- mysqrt.cxx
# ---------- if HAVE_LOG HAVE_EXP
# ------------ exp(log(x) * 0.5)
# ---------- else
# ------------ ...
# -----else
# ------ cmath
# -------- sqrt
#
# -- MakeTable: exe
# ---- MakeTable.cxx
#
#
# new struction
#
# -- Tutorial: exe
# ---- TutorialConfig.h
# ---- Tutorial.xxx
# ---- MathFunctions: lib
# ------ if USE_MYMATH
# -------- MakeTable: exe
# ---------- MakeTable.cxx
# -------- SqrtLibrary: lib
# ---------- mysqrt.cxx
# ---------- Table.h
# ------ else
# -------- cmath
# ---------- sqrt
# 

add_subdirectory(MathFunctions)

# add the executable
add_executable(Tutorial tutorial.cxx)
target_link_libraries(Tutorial PUBLIC MathFunctions)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(Tutorial PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

# add the install targets
install(TARGETS Tutorial DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"
  DESTINATION include
  )

# enable testing
include(CTest)

# does the application run
add_test(NAME Runs COMMAND Tutorial 25)

# does the usage message work?
add_test(NAME Usage COMMAND Tutorial)
set_tests_properties(Usage
  PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number"
  )

# define a function to simplify adding tests
function(do_test target arg result)
  add_test(NAME Comp${arg} COMMAND ${target} ${arg})
  set_tests_properties(Comp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction(do_test)

# do a bunch of result based tests
do_test(Tutorial 4 "4 is 2")
do_test(Tutorial 9 "9 is 3")
do_test(Tutorial 5 "5 is 2.236")
do_test(Tutorial 7 "7 is 2.645")
do_test(Tutorial 25 "25 is 5")
do_test(Tutorial -25 "-25 is [-nan|nan|0]")
do_test(Tutorial 0.0001 "0.0001 is 0.01")

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
include(CPack)

cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Tutorial VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message("USE_MYMATH = ${USE_MYMATH}")

option(USE_MYMATH "Use tutorial provided math implementation" ON)
#[[
option:
Provide an option that the user can optionally select.
If no initial <value> is provided, OFF is used.
If <variable> is already set as a normal variable then the command does nothing
]]

# configure_file(TutorialConfig.h.in TutorialConfig.h)

message("USE_MYMATH = ${USE_MYMATH}")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(TutorialConfig.h.in TutorialConfig.h)

#[[
in configure_file
#cmakedefine VAR … -> #define VAR …
depending on whether VAR is set in CMake to any value not considered a false constant by the if() command. 
The “…” content on the line after the variable name, if any, is processed as above. 
Input file lines of the form #cmakedefine01 VAR will be replaced with either #define VAR 1 or #define VAR 0 similarly. 
#cmakedefine01 VAR -> #define VAR 0     : VAR not setted or OFF
#cmakedefine01 VAR -> #define VAR 1     : VAR setted and ON
]]

# option(USE_MYMATH "Use tutorial provided math implementation" OFF)

message("USE_MYMATH = ${USE_MYMATH}")

#[[
Exercise: Why is it important that we configure TutorialConfig.h.in after the option for USE_MYMATH? What would happen if we inverted the two?
Attention: get rid of the influence of CMake cache!!!

Use ccmake or the CMake GUI to update the value of USE_MYMATH. Rebuild and run the tutorial again. Which function gives better results, sqrt or mysqrt?
If option after configure_file (#cmakedefine before set it ON), USE_MYMATH will be undef in TutorialConfig.h like:
/* #undef USE_MYMATH */
]]

# add the MathFunctions library
# add_subdirectory(MathFunctions)
if(USE_MYMATH)
  add_subdirectory(MathFunctions)
  list(APPEND EXTRA_LIBS MathFunctions)
  list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/MathFunctions")
endif()

set(USE_KEY "hello")
message(STATUS "USE_KEY = ${USE_KEY}")

# print every element of list
function(print_list arg)
  list(LENGTH ${ARGV0} argv_len)
  message(STATUS "length of ${ARGV0}: ${argv_len}")
  set(i 0)
  while( i LESS ${argv_len})
    list(GET ${ARGV0} ${i} argv_value)
    message(STATUS "${ARGV0}[${i}]: ${argv_value}")
    math(EXPR i "${i} + 1")
  endwhile()
endfunction()

print_list(EXTRA_LIBS)
print_list(EXTRA_INCLUDES)

message(STATUS "EXTRA_LIBS = ${EXTRA_LIBS}")
message(STATUS "EXTRA_INCLUDES = ${EXTRA_INCLUDES}")

# add the executable
add_executable(Tutorial tutorial.cxx)

# target_link_libraries(Tutorial PUBLIC MathFunctions)
target_link_libraries(Tutorial PUBLIC ${EXTRA_LIBS})

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(Tutorial PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           ${EXTRA_INCLUDES}
                           )

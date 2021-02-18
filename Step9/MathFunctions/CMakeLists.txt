## first we add the executable that generates the table
#add_executable(MakeTable MakeTable.cxx)
#
## add the command to generate the source code
#add_custom_command(
#  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
#  COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
#  DEPENDS MakeTable
#  )

# add the main library
# add_library(MathFunctions
#             mysqrt.cxx
#             ${CMAKE_CURRENT_BINARY_DIR}/Table.h
#             )
add_library(MathFunctions MathFunctions.cxx)

# state that anybody linking to us needs to include the current source dir
# to find MathFunctions.h, while we don't.
# state that we depend on our binary dir to find Table.h
# target_include_directories(MathFunctions
#           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
#           PRIVATE   ${CMAKE_CURRENT_BINARY_DIR}
#           )
target_include_directories(MathFunctions
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )

# targets here:
# 1. MathFunctions.lib
# 2. SqrtLibrary.lib      when USE_MYMATH
# 3. MakeTable.exe

# should we use our own math functions
option(USE_MYMATH "Use tutorial provided math implementation" ON)
if(USE_MYMATH)
  # USE_MYMATH is ON
  # it means:
  # #define USE_MYMATH 1
  target_compile_definitions(MathFunctions PRIVATE "USE_MYMATH")

  # first we add the executable that generates the table
  add_executable(MakeTable MakeTable.cxx)

  # add the command to generate the source code
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    DEPENDS MakeTable
    )

  # library that just does sqrt
  add_library(SqrtLibrary STATIC
              mysqrt.cxx
              ${CMAKE_CURRENT_BINARY_DIR}/Table.h
              )

  # state that we depend on our binary dir to find Table.h
  target_include_directories(SqrtLibrary PRIVATE
                             ${CMAKE_CURRENT_BINARY_DIR}    # for locating Table.h
                             )

#  # no need:
#  # state that SqrtLibrary need PIC when the default is shared libraries
#  set_target_properties(SqrtLibrary PROPERTIES
#                        POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS}
#                        )

  # MathFunctions.lib use SqrtLibrary.lib
  target_link_libraries(MathFunctions PRIVATE SqrtLibrary)
endif()

message("====== USE_MYMATH = ${USE_MYMATH}")
message("====== EXPORTING_MYMATH = ${EXPORTING_MYMATH}")

## install rules
#install(TARGETS MathFunctions DESTINATION lib)
#install(FILES MathFunctions.h DESTINATION include)

# define the symbol stating we are using the declspec(dllexport) when
# building on windows
# telling code it's shared or static
target_compile_definitions(MathFunctions PRIVATE "EXPORTING_MYMATH" "BUILD_SHARED_LIBS")

message("====== USE_MYMATH = ${USE_MYMATH}")
message("====== EXPORTING_MYMATH = ${EXPORTING_MYMATH}")

# install rules
set(installable_libs MathFunctions)

# if(TARGET target-name)
#   True if the given name is an existing logical target name created by a call to the add_executable(), add_library(), or add_custom_target() command that has already been invoked (in any directory).
if(TARGET SqrtLibrary)
  list(APPEND installable_libs SqrtLibrary)
endif()

install(TARGETS ${installable_libs} DESTINATION lib)
install(FILES MathFunctions.h DESTINATION include)
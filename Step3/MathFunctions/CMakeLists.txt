add_library(MathFunctions mysqrt.cxx)

target_include_directories(MathFunctions
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )
#[[
We first state that anybody linking to MathFunctions needs to include the current source directory, while MathFunctions itself doesn’t. So this can become an INTERFACE usage requirement.

Remember INTERFACE means things that consumers require but the producer doesn’t. 

MathFunctions.lib(producer) don't do this include, because MathFunctions.c is complete.
MathFunctions.h only is provided for outer project(other exe or library, consumer here).
After this INTERFACE target_include_directories, we can omit include options for this headers in outer projects.
]]
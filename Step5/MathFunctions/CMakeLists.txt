add_library(MathFunctions mysqrt.cxx)

# find log and exp in platform
include(CheckSymbolExists)
check_symbol_exists(log "math.h" HAVE_LOG)
check_symbol_exists(exp "math.h" HAVE_EXP)
message("======1 ${HAVE_LOG}")
message("======1 ${HAVE_EXP}")

if(NOT (HAVE_LOG AND HAVE_EXP))
  message("====== log & exp not found in platform")

  unset(HAVE_LOG CACHE)
  unset(HAVE_EXP CACHE)

  message("======2 ${HAVE_LOG}")
  message("======2 ${HAVE_EXP}")

  # find log and exp in libm
  # found /usr/lib64/libm.so in centOS
  set(CMAKE_REQUIRED_LIBRARIES "m")
  check_symbol_exists(log "math.h" HAVE_LOG)
  check_symbol_exists(exp "math.h" HAVE_EXP)

## find library
# 
# 1. default path
#
# /usr/lib
# /lib
#
# 2. environment variable
#
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:...
#
# 3. ldconfig
#
## get all extra library
# cat /etc/ld.so.conf.d/* 
#
## add library path
## for example: opensIsl
# echo "/usr/local/ssl/lib" >> /etc/ld.so.conf.d/openssl.conf
# ldconfig
#
# 4. build with param
#
# -Wl£¬ -rpath
#


  message("======3 ${HAVE_LOG}")
  message("======3 ${HAVE_EXP}")

  if(HAVE_LOG AND HAVE_EXP)
    message("====== log & exp not found in libm")
    target_link_libraries(MathFunctions PRIVATE m)
  else()
    message("====== log & exp not found in libm")
  endif()

# clear cache
# don't have marco HAVE_LOG HAVE_EXP anymore
#
#  unset(HAVE_LOG CACHE)
#  unset(HAVE_EXP CACHE)
#
#  message("======4 ${HAVE_LOG}")
#  message("======4 ${HAVE_EXP}")

endif()

# state that anybody linking to us needs to include the current source dir
# to find MathFunctions.h, while we don't.
target_include_directories(MathFunctions
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )

# variable ==> marco
if(HAVE_LOG AND HAVE_EXP)
  target_compile_definitions(MathFunctions
                             PRIVATE "HAVE_LOG" "HAVE_EXP")
endif()

unset(HAVE_LOG CACHE)
unset(HAVE_EXP CACHE)

message("======5 ${HAVE_LOG}")
message("======5 ${HAVE_EXP}")

# install rules
install(TARGETS MathFunctions DESTINATION lib)
install(FILES MathFunctions.h DESTINATION include)

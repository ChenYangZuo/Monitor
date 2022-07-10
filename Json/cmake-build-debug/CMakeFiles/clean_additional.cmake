# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Json_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Json_autogen.dir\\ParseCache.txt"
  "Json_autogen"
  )
endif()

# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\UdpServer_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\UdpServer_autogen.dir\\ParseCache.txt"
  "UdpServer_autogen"
  )
endif()

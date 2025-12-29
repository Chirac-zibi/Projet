# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Projets_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Projets_autogen.dir\\ParseCache.txt"
  "Projets_autogen"
  )
endif()

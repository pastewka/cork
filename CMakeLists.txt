project (cork64)

cmake_minimum_required (VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
include(muspectreTools)
add_external_package(gmp)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()


include_directories(
  "${CMAKE_SOURCE_DIR}"
  "${CMAKE_SOURCE_DIR}/src/accel"
  "${CMAKE_SOURCE_DIR}/src/file_formats"
  "${CMAKE_SOURCE_DIR}/src/isct"
  "${CMAKE_SOURCE_DIR}/src/math"
  "${CMAKE_SOURCE_DIR}/src/mpz"
  "${CMAKE_SOURCE_DIR}/src/mesh"
  "${CMAKE_SOURCE_DIR}/src/rawmesh"
  "${CMAKE_SOURCE_DIR}/src/util")
  # "${CMAKE_SOURCE_DIR}/src/tetgen")

# set (CMAKE_STATIC_COMPILER "g++-7)
# set (CMAKE_CC_COMPILER "clang")
# set (CMAKE_CC_FLAGS  "-w -Wno-conversion ${INC} -g -fPIC")


# set (CMAKE_CXX_COMPILER "clang++")
# set (CMAKE_CXX_FLAGS  "-w -Wno-conversion ${INC} -g -DTETLIBRARY -fPIC")

# include_directories("./")
# include_directories("{CMAKE_SOURCE_DIR}")


add_subdirectory("${CMAKE_SOURCE_DIR}/src")

add_executable(cork_exe "${CMAKE_SOURCE_DIR}/src/main.cpp")
target_link_libraries(cork_exe PUBLIC corkpp)

cmake_minimum_required(VERSION 3.5.0)
find_library(MODBUS modbus)
#message("${MODBUS}")
#message("${CMAKE_LIBRARY_PATH}")
set(EXECUTABLE_OUTPUT_PATH "bin")
add_executable(modbus_rtu_read src/modbus_read.cpp)
add_executable(modbus_rtu_write src/modbus_write.cpp)
target_link_libraries(modbus_rtu_write  ${MODBUS})
target_link_libraries(modbus_rtu_read ${MODBUS})
#SET(CPACK_GENERATOR "DEB")
#SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "David Doria") #required

#INCLUDE(CPack)
#include(mb/ab.cmake)
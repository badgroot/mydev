cmake_minimum_required(VERSION 3.5.0)
message("Cmake start")
project("JSON_data_handling")
SET(CMAKE_CXX_STANDARD 11)
find_library(JSONCPP jsoncpp)
message("${JSONCPP}")
IF(${JSONCPP} STREQUAL "")
message("jsoncpp library not found")

ELSE()
message("jsoncpp library found!!!")
ENDIF(${JSONCPP} STREQUAL "")
if("${CMAKE_TOOLCHAIN_FILE}" STREQUAL "")
message("tool chain file not provide")
else()
message("toolchain file found")

endif()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/in.json
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/out.json
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_library(jsoncpp SHARED IMPORTED GLOBAL)
add_executable(jsonReadWrite main.cpp)
target_link_libraries(jsonReadWrite ${JSONCPP})

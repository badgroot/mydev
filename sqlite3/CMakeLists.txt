cmake_minimum_required(VERSION 3.5.0)
project(sqlite3)
SET(CMAKE_CXX_STANDARD 11)
find_library(SQLite3 NAMES sqlite3 PATHS ${LIB_DIR_LOCATION})
find_library(JSON jsoncpp)
if (${SQLITE3})
message(" SQLITE3 LIB FOUND")
endif (${SQLITE3})
if(${JSON})
message("JSON LIB FOUND")
endif(${JSON})
include_directories(inc/)
add_executable(sqlite1 src/main.cpp src/database.cpp)
target_link_libraries(sqlite1 "${SQLite3}" "${JSON}")
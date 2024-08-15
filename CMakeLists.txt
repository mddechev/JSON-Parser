cmake_minimum_required(VERSION 3.10)

project(JSONParser VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/includes)

# Add all source files
file(GLOB_RECURSE SOURCES 
    "${PROJECT_SOURCE_DIR}/source/*.cpp"
    "${PROJECT_SOURCE_DIR}/source/utility/*.cpp"
    "${PROJECT_SOURCE_DIR}/source/json_types/*.cpp"
    "${PROJECT_SOURCE_DIR}/source/commands/*.cpp"
)

# Add the executable
add_executable(json_parser ${SOURCES} ${PROJECT_SOURCE_DIR}/main.cpp)

# Optionally, you can add installation rules
install(TARGETS json_parser DESTINATION bin)

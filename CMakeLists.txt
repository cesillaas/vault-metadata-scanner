cmake_minimum_required(VERSION 3.10)
project(VaultMetadataScanner)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

add_executable(scanner src/main.cpp)
target_link_libraries(scanner ${CURL_LIBRARIES})

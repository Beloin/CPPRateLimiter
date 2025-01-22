cmake_minimum_required(VERSION 3.28)

project(rate_limiter)

include_directories(./include)

# TODO: Include boost

add_executable(rate_limiter main.cpp)

add_subdirectory(src)
add_subdirectory(lib)

target_link_libraries(
  rate_limiter
  src_lib
  lib_lib
)

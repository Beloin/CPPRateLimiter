cmake_minimum_required(VERSION 3.31)

foreach(lib_target ${Boost_LIBRARIES})
  get_target_property(lib_location ${lib_target} LOCATION)
  install(FILES ${lib_location} DESTINATION lib)
endforeach()

project(rate_limiter)

include_directories(./include)

add_executable(rate_limiter main.cpp)

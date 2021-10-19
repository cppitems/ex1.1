cmake_minimum_required(VERSION 3.0)

project(Ex0)

#set the required CPP standard for the project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set CXX flags for the compiler to be very strict
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -pedantic")

## Enable Clang sanitizer for memory warnings during Debug builds
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
  # -fsanitize=thread")
  # -fsanitize=memory")
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUGS} -fno-omit-frame-pointer -fsanitize=address")
  # -fsanitize=memory")
  # -fsanitize=thread")
endif()

# Define our library name
set(MY_LIBRARY "Widget")

file(GLOB MY_LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/lib/*.cpp")
set(MY_LIBRARY_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")

# build the library
if(MY_LIBRARY_SOURCES)
  message(STATUS "Building shared library")
  add_library(${MY_LIBRARY} SHARED ${MY_LIBRARY_SOURCES})
  target_include_directories(${MY_LIBRARY} PUBLIC "${MY_LIBRARY_INCLUDE_DIRS}")
else(MY_LIBRARY_SOURCES)
  message(STATUS "Building header-only library")
  add_library(${MY_LIBRARY} INTERFACE)
  target_include_directories(${MY_LIBRARY} INTERFACE "${MY_LIBRARY_INCLUDE_DIRS}")
endif(MY_LIBRARY_SOURCES)


# buy default tests are built, but this can be turned off
# command line: cmake -DBUILD_TESTS=OFF ..
# or use ccmake (simple GUI for cmake): press 'c' to configure cmake,
# then 'g' to generate makefile, options can be changed by highlighting them and pressing ENTER
option(BUILD_MY_TESTS "Build unit tests." ON)
if(BUILD_MY_TESTS)
  # Activate CTest testing framework
  enable_testing()
  # Add all tests in folder "tests" to the testing
  add_subdirectory("tests")
endif()

# Now build additional target to execute benchmarks
# of the different types of implementations
option(BUILD_BENCHMARK "Build the benchmark" ON)
if(BUILD_BENCHMARK)
  set(BENCHMARK_NAME "benchmark")
  add_executable(${BENCHMARK_NAME} "src/${BENCHMARK_NAME}.cpp")
  target_include_directories(${BENCHMARK_NAME} PUBLIC "${MY_LIBRARY_INCLUDE_DIRS}")
  target_link_libraries(${BENCHMARK_NAME} PRIVATE ${MY_LIBRARY})
endif()

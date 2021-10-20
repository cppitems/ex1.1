cmake_minimum_required(VERSION 3.0)

# set up the project for building all tests
project(Tests LANGUAGES CXX)

# make a custom target for usage with make
# all tests can be built using `make myTests`
add_custom_target(myTests)

set(MY_TEST_NAMES "")
list(APPEND MY_TEST_NAMES "TestA_rref")
list(APPEND MY_TEST_NAMES "TestB_lref")
list(APPEND MY_TEST_NAMES "TestC_value")

foreach(MY_TEST_NAME ${MY_TEST_NAMES})
  add_executable(${MY_TEST_NAME} ${MY_TEST_NAME}.cpp testasserts.hpp)
  target_link_libraries(${MY_TEST_NAME} PRIVATE ${MY_LIBRARY})

  # Add to test framework, so test can be built with `make myTests`
  add_dependencies(myTests ${MY_TEST_NAME})
  add_test(NAME ${MY_TEST_NAME} COMMAND ${MY_TEST_NAME})
endforeach(MY_TEST_NAME ${MY_TEST_NAMES})

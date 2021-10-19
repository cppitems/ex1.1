#pragma once

#include <stdexcept>

// define test assertion, which will throw if condition is false
#define TEST_ASSERT(condition, message)                                        \
  {                                                                            \
    if (!(condition)) {                                                        \
      throw std::runtime_error(                                                \
          std::string(__FILE__) + std::string(":") +                           \
          std::to_string(__LINE__) + std::string(" in ") +                     \
          std::string(__PRETTY_FUNCTION__) + "\nERROR: " + message);           \
    }                                                                          \
  }

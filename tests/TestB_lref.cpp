#include <Widget.hpp>

#include "testasserts.hpp"

/*
  This test checks whether rvref::set actually moves the passed vector
  correctly.
*/

int main() {
  // ctor: length '1000', init with '10'
  auto vec = Vector(1000, 10);

  auto originalPointer = vec.data();
  auto originalVec = vec;  // copy vec

  // use l-value to set new element and return l-value reference
  auto myWidget = lvref::init(vec);

  // test whether the original data is still valid
  TEST_ASSERT(vec.data() != nullptr, "vector was moved from l-value");
  // check if the original vector points to the same memory location
  TEST_ASSERT(myWidget.vec.data() != vec.data(),
              "new vector references the same data as old vector although it should be copied")
  // check if the original vector has the correct size
  TEST_ASSERT(vec == originalVec,
              "vector changed size during copying")
  // check if the new vector really is a new one
  TEST_ASSERT(myWidget.vec.data() != originalPointer,
              "new vector was moved into widget from l-value")
  // check if the new vector is the same as the old one
  TEST_ASSERT(myWidget.vec == originalVec,
  "vector changed during moving")

  return 0;
}

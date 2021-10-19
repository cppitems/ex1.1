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

  // use r-value reference to initialise
  auto myWidget = rvref::init(std::move(vec));

  // test whether the data is acutally moved correctly
  TEST_ASSERT(vec.data() == nullptr,
              "vec was not moved into the Widget when using an r-value");
  // test whether the final vector data is equivalent to the original one
  TEST_ASSERT(originalPointer == myWidget.vec.data(),
              "vector data was not moved into newVec after rvref::init");
  // check if the vector is still the same
  TEST_ASSERT(originalVec == myWidget.vec,
              "vector changed during moving")

  return 0;
}

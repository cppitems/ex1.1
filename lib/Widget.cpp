#include <iostream>
#include <random>

#include <Widget.hpp>

// EX1.1 implementation source

// Add your implementation of all function
// overloads for 'init' declared in Widget.hpp here.

Widget rvref::init(Vector &&vec) {
  return Widget{vec};
}

Widget lvref::init(Vector &vec) {
  return Widget{vec};
}

Widget value::init(Vector vec) {
  return Widget{vec};
}
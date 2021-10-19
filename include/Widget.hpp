#pragma once

// EX1.1 implementation header
#include <vector>

using Vector = std::vector<unsigned>;

struct Widget {
  Vector vec;
};

namespace rvref {
/// This function takes an r-value Vector,
/// and constructs a Widget with it
Widget init(Vector &&rref);
} // namespace rvref

namespace lvref {
/// This function takes an l-value Vector,
/// and constructs a Widget with it
Widget init(Vector &vec);
} // namespace lvref

namespace value {
/// This function takes a Vector by value,
/// and constructs a Widget with it
Widget init(Vector vec);
} // namespace value
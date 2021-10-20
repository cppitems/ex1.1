#include <chrono>
#include <iostream>
#include <iomanip>
   
#include <Widget.hpp>
  
// measures the runtime for initialization using
// a rvalue reference
// a const lvalue reference
// a value
template<bool MOVE, class TESTFUNC>
double runtest(std::vector<Vector> initial, TESTFUNC func) {
  using Clock = std::chrono::steady_clock;
  using Duration = std::chrono::duration<double>;

  auto start = Clock::now();
  for (auto &it : initial) {
    // if constexpr makes sure the if is evaluated at compiletime
    if constexpr(MOVE)
      // call func with r-value if compile-time MOVE is true
      func(std::move(it));
    else
      func(it);
  }
  auto stop = Clock::now();
  return Duration(stop - start).count() / initial.size();
}


int main() {
  std::size_t size = 10'000'000; // vector length 10M == ~40MB
  std::size_t n = 5;            // iterations for averaging run time

  // make n vectors that we want to use to initialise n instances of Widget
  std::vector<Vector> initialValues(n, Vector(size, 42));

  std::cout << std::scientific;
  std::cout << std::setprecision(2);

  std::cout << "Function runtimes called with Vector object vec:\n\n";

  auto rrefTime = runtest<true>(initialValues, rvref::init);
  std::cout << "rvref::init(Vector&&) called as rvref::init(std::move(vec))  " << rrefTime << " s" << std::endl;

  auto lrefTime = runtest<false>(initialValues, lvref::init);
  std::cout << "lvref::init(Vector&)  called as lvref::init(vec)             " << lrefTime << " s" << std::endl;

  auto rvalTime = runtest<true>(initialValues, value::init);
  std::cout << "value::init(Vector)   called as value::init(std::move(vec))  " << rvalTime << " s" << std::endl;

  auto lvalTime = runtest<false>(initialValues, value::init);
  std::cout << "value::init(Vector)   called as value::init(vec)             " << lvalTime << " s" << std::endl;

  std::cout << "\n" << std::endl;

  return EXIT_SUCCESS;
}
#include "binomial_coefficients.h"
#include <array>
#include <cassert>
#include <chrono>

// This implementation of Pascal's Triangle uses two tricks:
// 1. Caches previous computations, for efficiency
// 2. Doesn't store the obvious results, i.e. the leading and trailing 1 which
// appear at all lines and also the first element of Pascal triangle, which is
// also 1 [ (0,0) => 1 ] That's why the vector of vectors is called coreCache.
// I'm not caching all the things, just the core of the triangle. Because of
// that the first two rows are not stored and for all other rows the first and
// last column are not stored as well. This implies in:
// 1. All row references must be subtracted by 2 when accessing the vector
// 2. All column references must be subtracted by 1 when accessing the vector.
class PascalTriangle {
private:
  std::vector<std::vector<unsigned int>> coreCache;

  void computeCacheUntil(unsigned int n) {
    for (unsigned int row = coreCache.size(); row < n; ++row) {
      coreCache.emplace_back(std::vector<unsigned int>(row + 1));
      coreCache[row][0] = row + 2;
      for (unsigned int column = 1; column <= row; ++column) {
        // Decision if emulate the 1 not stored at the end of the row.
        unsigned int n_1_chooses_k =
            (column > row - 1 ? 1 : coreCache[row - 1][column]);
        unsigned int coeff = n_1_chooses_k + coreCache[row - 1][column - 1];
        coreCache[row][column] = coeff;
      }
    }
  }

public:
  // std::initializer_list<unsigned int>{2u} is needed just to silence warning
  // about a scalar surrounded by curly brackets - initializer_list thing.
  PascalTriangle() : coreCache{{std::initializer_list<unsigned int>{2u}}} {}

  unsigned int max_n_cached() { return coreCache.size() + 1; }

  unsigned int bin(unsigned int n, unsigned int k) {
    // This avoids storing some 1s unnecessarily.
    if (n == 0 || k == 0 || n == k)
      return 1u;
    // And this avoid repeat computations.
    if (n <= max_n_cached())
      return coreCache[n - 2][k - 1];

    computeCacheUntil(n);
    return coreCache[n - 2][k - 1];
  }
};

unsigned int bin(unsigned int n, unsigned int k) {
  static PascalTriangle _pascal;
  return _pascal.bin(n, k);
}

int main(int argc, char *argv[]) {
  std::array<std::array<unsigned int, 3>, 7> expected{{{0, 0, 1},
                                                       {5, 0, 1},
                                                       {2, 2, 1},
                                                       {5, 5, 1},
                                                       {7, 2, 21},
                                                       {5, 3, 10},
                                                       {8, 5, 56}}};

  for (const auto &exp : expected) {
    std::cout << "Testing n=" << exp[0] << ", k=" << exp[1] << "\t";
    auto start = std::chrono::steady_clock::now();
    unsigned int actual = bin(exp[0], exp[1]);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> seconds = end - start;
    std::cout << "actual=" << actual << "\t with duration: " << seconds.count();
    assert(exp[2] == actual);
    std::cout << " == ok\n";
  }
}

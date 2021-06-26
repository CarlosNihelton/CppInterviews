#include "binomial_coefficients.h"

// This implementation of Pascal's Triangle uses two tricks:
// 1. Caches previous computations, for efficiency
// 2. Doesn't store the obvious results, i.e. the leading and trailing 1 which
// appear at all lines and also the first element of Pascal triangle, which is
// also 1 [ (0,0) => 1 ] That's why the vector of vectors is called coreCache->
// I'm not caching all the things, just the core of the triangle. Because of
// that the first two rows are not stored and for all other rows the first and
// last column are not stored as well. This implies in:
// 1. All row references must be subtracted by 2 when accessing the vector
// 2. All column references must be subtracted by 1 when accessing the vector.
//
// Since there are quite a lot of possible values for n and k which results in
// obvious values, another small optimization implmented is wrapping the cached
// result collection into an optional, so that I can defer its creation until
// the moment it is actually required.
class PascalTriangle {
private:
  std::optional<std::vector<std::vector<unsigned long>>> coreCache;

  void computeCacheUntilRow(unsigned int n) {
    if (!coreCache.has_value()) {
      coreCache.emplace(
          std::initializer_list<std::vector<unsigned long>>{{2u}});
    }
    for (unsigned int row = coreCache->size(); row < n; ++row) {
      coreCache->emplace_back(std::vector<unsigned long>(row + 1));
      auto &cache = coreCache.value();
      cache[row][0] = row + 2;
      cache[row][row] = row + 2;
      for (unsigned int column = 1; column < row; ++column) {
        cache[row][column] =
            cache[row - 1][column] + cache[row - 1][column - 1];
      }
    }
  }

public:
  unsigned int max_n_cached() { return coreCache->size() + 1; }

  unsigned long bin(unsigned int n, unsigned int k) {
    // This avoids storing some 1s unnecessarily.
    if (n == 0 || k == 0 || n == k)
      return 1u;
    if (k == 1 || n - k == 1)
      return n;
    // And this ensures caching new calculations.
    if (n > max_n_cached())
      computeCacheUntilRow(n);

    return coreCache.value()[n - 2][k - 1];
  }
};

unsigned long bin(unsigned int n, unsigned int k) {
  static PascalTriangle _pascal;
  return _pascal.bin(n, k);
}

int main(int argc, char *argv[]) {
  std::array<std::array<unsigned int, 3>, 10> expected{
      {{0, 0, 1},
       {5, 0, 1},
       {2, 2, 1},
       {5, 5, 1},
       {23, 22, 23},
       {590, 1, 590},
       {7, 2, 21},
       {5, 3, 10},
       {8, 5, 56},
       {29, 19, 20030010}}};

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

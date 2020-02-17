#ifndef INLINE_VECTOR_H_
#define INLINE_VECTOR_H_

#include <algorithm>
#include <array>
#include <cassert>
#include <limits>
#include <sstream>
#include <vector>

template <typename T, uint16_t N>
class InlineVector {
public:
  explicit InlineVector(TRootIOCtor *io_ctor) {} // Constructor for ROOT I/O
  InlineVector() {}

  virtual ~InlineVector() {}

  T &operator[](uint16_t index) { return data_[index]; }

private:
  std::array<T, N> data_;
  uint16_t size_ = 0;

  ClassDef(InlineVector, 1); // NOLINT
};

#endif // INLINE_VECTOR_H_

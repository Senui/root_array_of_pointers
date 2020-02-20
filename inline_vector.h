#ifndef INLINE_VECTOR_H_
#define INLINE_VECTOR_H_

#include <array>
#include <iostream>
#include <fstream>

#include "Rtypes.h"
#include "TBuffer.h"
#include "TClassTable.h"

template <typename T>
class VectorWrapper {
public:
  VectorWrapper() {}

  std::vector<T> vector_;
  ClassDefNV(VectorWrapper, 1);
};

template <typename T, uint16_t N>
class InlineVector {
public:
  InlineVector() {}

  explicit InlineVector(TRootIOCtor *io_ctor) {} // Constructor for ROOT I/O

  T &operator[](uint16_t index) { return data_[index]; }

  void push_back(const T& element) {
    data_[size_++] = element;
  }

private:
  std::array<T, N> data_; //!
  uint16_t size_ = 0;
  ClassDefNV(InlineVector, 1);
};

// template <typename T, uint16_t N>
template <>
inline void InlineVector<int,2>::Streamer(TBuffer &R__b) {
  if (R__b.IsReading()) {
    std::cout << "READING..." << std::endl;
    VectorWrapper<int> vw;
    R__b.ReadClassBuffer(TClassTable::GetDict("VectorWrapper<int>")(), &vw);
    // tranfer vw to this
    std::cout << "vector.size() =  " << vw.vector_.size() << std::endl;
    for (auto ve : vw.vector_) {
      std::cout << ve << std::endl;
      this->push_back(ve);
    }
  } else {
    // transfer data from this to f
    std::cout << "WRITING..." << std::endl;
    VectorWrapper<int> vw;
    vw.vector_.resize(size_);
    for (uint16_t i = 0; i < size_; i++) {
      std::cout << "value " << data_[i] << std::endl;
      vw.vector_[i] = data_[i];
    }
    R__b.WriteClassBuffer(TClassTable::GetDict("VectorWrapper<int>")(), &vw);
  }
}

#ifdef __ROOTCLING__
#include "TObject.h"
static InlineVector<int, 2> iv3;
#endif

#endif // INLINE_VECTOR_H_

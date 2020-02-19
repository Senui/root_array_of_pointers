#ifndef INLINE_VECTOR_H_
#define INLINE_VECTOR_H_

#include <array>
#include <iostream>
#include <fstream>

#include "Rtypes.h"
#include "TBuffer.h"

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

template <typename T, uint16_t N>
void InlineVector<T, N>::Streamer(TBuffer &R__b) {
  std::ofstream file;
  file.open("streamer.log");
  if (R__b.IsReading()) {
    file << "READING..." << std::endl;
    VectorWrapper<T> vw;
    R__b.ReadClassBuffer(VectorWrapper<T>::Class(), &vw);
    R__b.ReadClassBuffer(InlineVector<T, N>::Class(), this);
    // tranfer vw to this
    file << vw.vector_ << std::endl;
    for (auto *ve : vw.vector_) {
      file << ve << std::endl;
      file << ve->GetUniqueID() << std::endl;
      this->push_back(ve);
    }
  } else {
    // transfer data from this to f
    file << "WRITING..." << std::endl;
    VectorWrapper<T> vw;
    vw.vector_.resize(this->size_);
    for (uint16_t i = 0; i < this->size_; i++) {
      vw.vector_[i] = this->data_[i];
    }
    R__b.WriteClassBuffer(VectorWrapper<T>::Class(), &vw);
    R__b.WriteClassBuffer(InlineVector<T, N>::Class(), this);
  }
}

#ifdef __ROOTCLING__
#include "TObject.h"
static InlineVector<TObject *, 2> iv3;
#endif

#endif // INLINE_VECTOR_H_

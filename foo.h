#ifndef FOO_H_
#define FOO_H_

#include <array>

#include <Rtypes.h>
#include <TObject.h>

// class Base {
// public:
//   Base() {}
//   virtual ~Base() {}

// private:
//   int base_ = 123;
//   ClassDef(Base, 1);
// };

class Foo {
public:
  Foo() {}
  // Foo(TRootIOCtor*) {
  //   foo_[0] = nullptr;
  //   foo_[1] = nullptr;
  // }

  void Create() {
    foo_[0] = new TObject();
    foo_[1] = new TObject();
  }

  std::array<TObject*, 2> foo_;
  ClassDefNV(Foo, 1);
};

#endif  // FOO_H_

#ifndef FOO_H_
#define FOO_H_

#include <iostream>
#include <array>
#include <vector>

#include "TBuffer.h"
#include <Rtypes.h>

#include "inline_vector.h"

#define ARRAY

class Base {
public:
  Base() {}
  virtual ~Base() {}

private:
  int base_ = 123;
  ClassDef(Base, 1);
};

class Foo : public Base {
public:
  Foo() {}
  Foo(int foo) : foo_(foo) {}
  virtual ~Foo() {}

  int GetA() { return foo_; }

private:
  int foo_ = 0;
  ClassDefOverride(Foo, 1);
};

class Bar {
  public:
  Bar() {}
#ifdef INLINE_VECTOR
  Bar(const InlineVector<Base*, 2>& v) : bar_(v) {}
#elif defined(ARRAY)
  Bar(const std::array<Base*, 2>& v) : bar_(v) {}
#else
  Bar(const std::vector<Base*>& v) : bar_(v) {}
#endif
  virtual ~Bar() {}

private:
#ifdef INLINE_VECTOR
  InlineVector<Base*, 2> bar_;
#elif defined(ARRAY)
  std::array<Base*, 2> bar_;
#else
  std::vector<Base*> bar_;
#endif
  ClassDef(Bar, 1);
};

#endif // FOO_H_

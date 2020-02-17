#ifndef FOO_H_
#define FOO_H_

#include <array>

#include <Rtypes.h>

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

private:
  int foo_ = 0;
  ClassDefOverride(Foo, 1);
};

#endif  // FOO_H_

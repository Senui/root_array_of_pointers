#include "foo.h"

#include <TFile.h>

#include <array>
#include <iostream>

static constexpr char const *kFile = "foo.root";
static constexpr char const *kObjName = "foo";

int main() {
  Foo foo;
  foo.Create();

  TFile f(kFile, "RECREATE");
  f.WriteObject(&foo, kObjName);
  f.Close();

  TFile ff(kFile);
  // std::array<Foo*, 2> *arr2 = nullptr;
  Foo *foo2 = nullptr;
  ff.GetObject(kObjName, foo2);

  std::cout << foo2 << std::endl;
  // bool valid = dynamic_cast<Foo*>((*arr2)[0]) != nullptr;
  // std::cout << valid << std::endl;

  return 0;
}

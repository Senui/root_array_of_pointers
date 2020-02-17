#include "foo.h"

#include <TFile.h>

#include <array>
#include <iostream>

static constexpr char const *kFile = "foo.root";
static constexpr char const *kObjName = "foo";

int main() {
  // std::array<Foo*, 2> arr;
  // arr[0] = new Foo(42);
  // arr[1] = new Foo(43);

  std::array<TObject*, 2> arr;
  arr[0] = new TObject();
  arr[1] = new TObject();

  TFile f(kFile, "RECREATE");
  f.WriteObject(&arr, kObjName);
  f.Close();

  delete arr[0];
  delete arr[1];

  TFile ff(kFile);
  // std::array<Foo*, 2> *arr2 = nullptr;
  std::array<TObject*, 2> *arr2 = nullptr;
  ff.GetObject(kObjName, arr2);

  std::cout << arr2 << std::endl;
  // bool valid = dynamic_cast<Foo*>((*arr2)[0]) != nullptr;
  // std::cout << valid << std::endl;

  return 0;
}

#include "foo.h"

#include "inline_vector.h"

#include "TBufferJSON.h"
#include <TFile.h>
#include <iostream>

#include <array>
#include <vector>

#ifdef INLINE_VECTOR
static constexpr char const *kJsonFile = "foo_ilv.json";
#elif defined(ARRAY)
static constexpr char const *kJsonFile = "foo_array.json";
#else
static constexpr char const *kJsonFile = "foo_vector.json";
#endif
static constexpr char const *kFile = "foo.root";
static constexpr char const *kObjName = "foo";

int main() {
#ifdef INLINE_VECTOR
  InlineVector<Base *, 2> ilv;
#elif defined(ARRAY)
  std::array<Base*, 2> ilv;
#else
  std::vector<Base *> ilv;
  ilv.resize(2);
#endif
  Foo *f1 = new Foo(42);
  Foo *f2 = new Foo(43);
  ilv[0] = f1;
  ilv[1] = f2;

  Bar b(ilv);
  TBufferJSON::ExportToFile(kJsonFile, &b, b.Class());

  TFile f(kFile, "RECREATE");
  f.WriteObject(&b, kObjName);
  f.Close();

  TFile ff(kFile);
  Bar *b2 = nullptr;
  ff.GetObject(kObjName, b2);

  // bool valid = dynamic_cast<Foo*>((*b2)[0]) != nullptr;
  // std::cout << valid << std::endl;

  std::cout << b2 << std::endl;
  return 0;
}

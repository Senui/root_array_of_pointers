#include "inline_vector.h"

#include <TFile.h>
#include <TObject.h>

#include <array>
#include <iostream>

static constexpr char const *kFile = "foo.root";
static constexpr char const *kObjName = "foo";

int main() {
  InlineVector<int, 2> iv;

  for (size_t i = 0; i < 2; i++) {
    iv[i] = 42 + i;
  }

  TFile f(kFile, "RECREATE");
  f.WriteObject(&iv, kObjName);
  f.Close();

  TFile ff(kFile);
  InlineVector<int, 2> *iv2 = nullptr;
  ff.GetObject(kObjName, iv2);

  std::cout << "iv2 = " << iv2 << std::endl;
  std::cout << "(*iv2)[1] = " << (*iv2)[1] << std::endl;

  return 0;
}

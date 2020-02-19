#include "inline_vector.h"

#include <TFile.h>
#include <TObject.h>

#include <array>
#include <iostream>

static constexpr char const *kFile = "foo.root";
static constexpr char const *kObjName = "foo";

int main() {
  InlineVector<TObject*, 2> iv;

  for (size_t i = 0; i < 2; i++) {
    TObject* o = new TObject(); o->SetUniqueID(i);
    iv[i] = o;
  }

  TFile f(kFile, "RECREATE");
  f.WriteObject(&iv, kObjName);
  f.Close();

  TFile ff(kFile);
  InlineVector<TObject*, 2> *iv2 = nullptr;
  ff.GetObject(kObjName, iv2);

  std::cout << "iv2 = " << iv2 << std::endl;
  std::cout << "(*iv2)[1] = " << (*iv2)[1] << std::endl;
  std::cout << "(*iv2)[1]->GetUniqueID() = " << (*iv2)[1]->GetUniqueID() << std::endl;

  return 0;
}

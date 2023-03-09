// #include "podio/EventStore.h"
// #include "podio/ROOTWriter.h"
// #include "write_test.h"

#include "TFile.h"
#include "TTree.h"
#include "datamodel/ExampleHitData.h"
#include "datamodel/ExampleHitCollection.h"
// #include "TestDataModelDict.cxx"

// class TTTree : public TTree {
// public:
//   TBranch* BranchImpRef(const char* branchname, const char *classname, TClass* ptrClass, void *addobj, Int_t bufsize, Int_t splitlevel)
//   { return TTree::BranchImpRef(const char* branchname, const char *classname, TClass* ptrClass, void *addobj, Int_t bufsize, Int_t splitlevel); }
// };

int main(int, char**) {

  TFile f("test.root", "RECREATE");
  TTree tree("test", "tree");

  auto hits = ExampleHitCollection();

  auto hits1 = ExampleHit(0xbad, 0., 0., 0., 23. + 0);

  hits.push_back(hits1);

  hits.prepareForWrite();
  auto buffers = hits.getBuffers();

  // ExampleHitData e;
  // std::vector<ExampleHitData> v {ExampleHitData(), ExampleHitData()};
  std::vector<ExampleHitData> vtest { {1, 2, 3, 4}};
  auto nptr = &vtest;

  void* ptr = buffers.data;
  auto vptr = (std::vector<ExampleHitData>*)ptr;
  std::cout << "Size is " << vptr->size() << std::endl;
  std::cout << (*vptr)[0].cellID << " " << (*vptr)[0].x << " " << (*vptr)[0].y << " " << (*vptr)[0].z << " " << (*vptr)[0].energy << std::endl;


  tree.Branch("events", "std::vector<ExampleHitData>", nptr);

  tree.Fill();
  tree.Write();

}

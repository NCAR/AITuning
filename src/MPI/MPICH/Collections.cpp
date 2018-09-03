#include <iostream>
#include <vector>
#include "Variables.h"
#include "MPICH/Collections_3_2_1.h"

using namespace std;

CollectionPerformanceVar CollectionCreatorMPICH::createCollectionPerformanceVar()
{
  CollectionPerformanceVar perf_collection("MPICH","3.2.1");
  
  return perf_collection;
}
  
CollectionControlVal CollectionCreatorMPICH::createCollectionControlVar()
{
  CollectionControlVar control_collection("MPICH","3.2.1");
  
  return control_collection;
}

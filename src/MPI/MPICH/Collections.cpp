#include <iostream>
#include <vector>

#include "Variables.h"
#include "Collections.h"
#include "Utility.h"

using namespace std;

class CollectionCreatorMPICH : public CollectionCreator
{
public:

  CollectionPerformanceVar createCollectionPerformanceVar()
  {
    CollectionPerformanceVar perf_collection("MPICH","3.2.1");
    
    
    return perf_collection;
  }
  
  CollectionControlVal createCollectionControlVar()
  {
    CollectionControlVar control_collection("MPICH","3.2.1");
    
    return control_collection;
  }
  
}

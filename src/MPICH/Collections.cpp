#include <iostream>
#include <vector>

#include "Variables.h"

using namespace std;

class CollectionCreatorOpenMPI : public CollectionCreator
{
public:

  CollectionPerformanceVar createCollectionPerformanceVar()
  {
    CollectionPerformanceVar collection = new CollectionPerformanceVar("Open-MPI","3.0.1");
    
    return collection;
  }
  
  CollectionControlVal createCollectionControlVar()
  {
    CollectionControlVar collection = new CollectionControlVar("Open-MPI","3.0.1");
    
    return collection;
  }

  
  
}

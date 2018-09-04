#include <iostream>
#include "MPI_T_Obj.h"
#include "Probes.h"
#include "mpi.h"
#include "MPICH/Collections_3_2_1.h"
#include "MPICH/Variables.h"

using namespace std;

int main(void)
{
  int provided;

  CollectionCreator *collectionFactory;

  //MPICH gets passed in some way

  collectionFactory = new CollectionCreatorMPICH();

  CollectionControlVar *collectionControlVars;
  CollectionPerformanceVar *collectionPerformanceVars;

  collectionControlVars = collectionFactory->createCollectionControlVar();
  collectionPerformanceVars = collectionFactory->createCollectionPerformanceVar();
  
  MPI_Init_thread(NULL,NULL,MPI_THREAD_FUNNELED,&provided);

  

  return 0;
}

#include <iostream>
#include "MPI_T_Obj.h"
#include "Probes.h"
#include "mpi.h"
#include "MPICH/Collections_3_2_1.h"
#include "MPICH/Variables.h"
#include "MVAPICH/Collections_2_3.h"
#include "MVAPICH/Variables.h"

using namespace std;

CollectionControlVar *collectionControlVars;
CollectionPerformanceVar *collectionPerformanceVars;

void AITuning_start(string layer)
{
  // int provided;

  CollectionCreator *collectionFactory;

  if(layer == "MPICH")
    collectionFactory = new CollectionCreatorMPICH();
  else if(layer=="MVAPICH" || "MVAPICH2")
    collectionFactory = new CollectionCreatorMVAPICH();
  else
    perror("Layer not supported");

  collectionControlVars = collectionFactory->createCollectionControlVar();
  collectionPerformanceVars = collectionFactory->createCollectionPerformanceVar();
}

void AITuning_addUserDefinedPerformanceVar(UserDefinedPerformanceVar *ud)
{
  collectionPerformanceVars->addPerformanceVariable(ud);
}

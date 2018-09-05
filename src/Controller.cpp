#include <iostream>
#include "MPI_T_Obj.h"
#include "Probes.h"
#include "mpi.h"
#include "MPICH/Collections_3_2_1.h"
#include "MPICH/Variables.h"

using namespace std;

CollectionControlVar *collectionControlVars;
CollectionPerformanceVar *collectionPerformanceVars;

void AITuning_start(string layer)
{
  // int provided;

  CollectionCreator *collectionFactory;

  if(layer == "MPICH")
    collectionFactory = new CollectionCreatorMPICH();
  else
    perror("Layer not supported");

  collectionControlVars = collectionFactory->createCollectionControlVar();
  collectionPerformanceVars = collectionFactory->createCollectionPerformanceVar();

  // UserDefinedPerformanceVar ud_perf_var("Total_time","myfile.txt");

  // collectionPerformanceVars->addPerformanceVariable(&ud_perf_var);
  
  // SingleProbe probe_time("Total_time_probe", &ud_perf_var);

  // probe_time.registerValue(100.0);
  // probe_time.registerValue(140.0);
  // printf("%lf\n",ud_perf_var.getLastValue());
}

void AITuning_addUserDefinedPerformanceVariable(UserDefinedPerformanceVar *ud)
{
  collectionPerformanceVars->addPerformanceVariable(ud);
}

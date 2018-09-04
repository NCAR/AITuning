#include <iostream>
#include "MPI_T_Obj.h"
#include "Probes.h"
#include "mpi.h"
#include "MPICH/Collections_3_2_1.h"
#include "MPICH/Variables.h"

using namespace std;

void AITuning_start(string layer)
{
  // int provided;

  CollectionCreator *collectionFactory;

  if(layer == "MPICH")
    collectionFactory = new CollectionCreatorMPICH();
  else
    perror("Layer not supported");

  CollectionControlVar *collectionControlVars;
  CollectionPerformanceVar *collectionPerformanceVars;

  collectionControlVars = collectionFactory->createCollectionControlVar();
  collectionPerformanceVars = collectionFactory->createCollectionPerformanceVar();
  
  // MPI_Init_thread(NULL,NULL,MPI_THREAD_FUNNELED,&provided);

  UserDefinedPerformanceVar ud_perf_var("Total_time","myfile.txt");

  collectionPerformanceVars->addPerformanceVariable(&ud_perf_var);
  
  SingleProbe probe_time("Total_time_probe", &ud_perf_var);

  probe_time.registerValue(100.0);
  probe_time.registerValue(140.0);
  printf("%lf\n",ud_perf_var.getLastValue());
}

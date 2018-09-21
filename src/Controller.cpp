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
static CollectionCreator *collectionFactory;

void AITuning_start(string layer)
{
  // int provided;

  if(layer == "MPICH")
    collectionFactory = new CollectionCreatorMPICH();
  else if(layer=="MVAPICH" || "MVAPICH2")
    collectionFactory = new CollectionCreatorMVAPICH();
  else
    perror("Layer not supported");
}

void AITuning_setControlVariables()
{
  collectionControlVars = collectionFactory->createCollectionControlVar();
}

void AITuning_dumpControlVariablesOnFile(bool first_run = false)
{
  collectionControlVars->dumpCollectionOnFile(first_run);
}

void AITuning_readControlVariablesFromFile()
{
  collectionControlVars->readCollectionFromFile();
}

void AITuning_readAIChanges()
{
  collectionControlVars->readAIChanges();
}

void AITuning_setPerformanceVariables()
{
  collectionPerformanceVars = collectionFactory->createCollectionPerformanceVar();
}

void AITuning_addUserDefinedPerformanceVar(UserDefinedPerformanceVar *ud)
{
  collectionPerformanceVars->addPerformanceVariable(ud);
}

void AITuning_readPerformanceVariables()
{
  collectionPerformanceVars->registerPerformanceVariables();
}

void AITuning_cleanRelativePerfVars()
{
  collectionPerformanceVars->cleanRelativePerformanceVariables();
}

vector<Statistics *> AITuning_generateStatistics()
{
  return collectionPerformanceVars->generateStatistics();
}

#include <iostream>
#include "MPI_T_Obj.h"
#include "Probes.h"
#include "mpi.h"
#include "Variables.h"
#include "Collections.h"

using namespace std;

int main(void)
{
  int provided;
  MPI_T_Manager mpi_t_manager;

  CollectionCreator *collectionFactory;

  //MPICH gets passed in some way

  collectionFactory = new CollectionCreatorMPICH();

  CollectionControlVariables *collectionControlVars;
  CollectionPerformanceVariables *collectionControlVars;

  collectionControlVars = collectionFactory->createCollectionControlVar();
  collectionPerformanceVars = collectionFactory->createCollectionPerformanceVar();

  mpi_t_manager.initialize_MPI_T();
  MPI_Init_thread(NULL,NULL,MPI_THREAD_FUNNELED,&provided);

  MPICHIntControlVariable eager_limit("MPIR_CVAR_CH3_EAGER_MAX_MSG_SIZE", 128, &mpi_t_manager);

  MPICHBoolControlVariable async_progress("MPIR_CVAR_ASYNC_PROGRESS", &mpi_t_manager);

  async_progress.printVar();
  async_progress.incrementVar();
  async_progress.printVar();
  
  return 0;
}

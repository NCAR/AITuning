#include <iostream>
#include <vector>
#include "Variables.h"
#include "MPICH/Collections_3_2_1.h"
#include "MPICH/Variables.h"

using namespace std;

CollectionCreatorMPICH::CollectionCreatorMPICH()
{
  control_vars = new CollectionControlVar("MPICH","3.2.1");
  performance_vars = new CollectionPerformanceVar("MPICH","3.2.1");

  ControlVariable *tmp = new MPICHBoolControlVariable("MPIR_CVAR_ASYNC_PROGRESS", &mpi_t_manager);
  control_vars.addControlVariable(tmp);
  tmp = new MPICHBoolControlVariable("MPIR_CVAR_CH3_ENABLE_HCOLL", &mpi_t_manager);
  control_vars.addControlVariable(tmp);
  tmp = new MPICHIntControlVariable("MPIR_CVAR_CH3_RMA_DELAY_ISSUING_FOR_PIGGYBACKING", 10, &mpi_t_manager);
  control_vars.addControlVariable(tmp);
  tmp = new MPICHIntControlVariable("MPIR_CVAR_CH3_RMA_OP_PIGGYBACK_LOCK_DATA_SIZE", 10, &mpi_t_manager);
  control_vars.addControlVariable(tmp);
  tmp = new MPICHIntControlVariable("MPIR_CVAR_POLLS_BEFORE_YIELD", 10, &mpi_t_manager);
  control_vars.addControlVariable(tmp);
  
  mpi_t_manager.initialize_MPI_T();
}

CollectionPerformanceVar *CollectionCreatorMPICH::createCollectionPerformanceVar()
{ 
  return performance_var;
}
  
CollectionControlVal *CollectionCreatorMPICH::createCollectionControlVar()
{
  return control_vars;
}

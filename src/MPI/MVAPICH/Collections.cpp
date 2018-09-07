#include <iostream>
#include <vector>
#include "Variables.h"
#include "MVAPICH/Collections_2_3.h"
#include "MVAPICH/Variables.h"

using namespace std;

CollectionCreatorMVAPICH::CollectionCreatorMVAPICH()
{
  mpi_t_manager.initialize_MPI_T();
  
  control_vars_ = new CollectionControlVar("MVAPICH","2.3");
  performance_vars_ = new CollectionPerformanceVar("MVAPICH","2.3");
  
  /* CONTROL VARIABLES */

  ControlVariable *tmp = new MVAPICHBoolControlVariable("MPIR_CVAR_ASYNC_PROGRESS", &mpi_t_manager);
  control_vars_->addControlVariable(tmp);

  tmp = new MVAPICHBoolControlVariable("MPIR_CVAR_USE_SHARED_MEM", &mpi_t_manager);
  control_vars_->addControlVariable(tmp);

  tmp = new MVAPICHBoolControlVariable("MPIR_CVAR_ENABLE_SHARP", &mpi_t_manager);
  control_vars_->addControlVariable(tmp);

  tmp = new MVAPICHBoolControlVariable("MPIR_CVAR_CH3_RMA_DELAY_ISSUING_FOR_PIGGYBACKING", &mpi_t_manager);
  control_vars_->addControlVariable(tmp);

  tmp = new MVAPICHBoolControlVariable("MPIR_CVAR_USE_MCAST", &mpi_t_manager);
  control_vars_->addControlVariable(tmp);

  tmp = new MVAPICHBoolControlVariable("MPIR_CVAR_CH3_ENABLE_HCOLL", &mpi_t_manager);
  control_vars_->addControlVariable(tmp);

  tmp = new MVAPICHIntControlVariable("MPIR_CVAR_CH3_RMA_OP_PIGGYBACK_LOCK_DATA_SIZE", 10, &mpi_t_manager);
  control_vars_->addControlVariable(tmp);

  tmp = new MVAPICHIntControlVariable("MPIR_CVAR_POLLS_BEFORE_YIELD", 10, &mpi_t_manager);
  control_vars_->addControlVariable(tmp);

  /* PERFORMANCE VARIABLES */

  

}

CollectionPerformanceVar *CollectionCreatorMVAPICH::createCollectionPerformanceVar()
{ 
  return performance_vars_;
}
  
CollectionControlVar *CollectionCreatorMVAPICH::createCollectionControlVar()
{
  return control_vars_;
}

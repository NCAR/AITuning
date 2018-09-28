#include <iostream>
#include <vector>
#include "Variables.h"
#include "MVAPICH/Collections_2_3.h"
#include "MVAPICH/Variables.h"

using namespace std;

CollectionCreatorMVAPICH::CollectionCreatorMVAPICH()
{
  mpi_t_manager.initialize_MPI_T();
}

CollectionPerformanceVar *CollectionCreatorMVAPICH::createCollectionPerformanceVar()
{
  performance_vars_ = new CollectionPerformanceVar("MVAPICH","2.3");

  /* PERFORMANCE VARIABLES */
  PerformanceVariable *tmp_p = new MVAPICHPerformanceVariable("mv2_smp_read_progress_poll_success", MPI_T_PVAR_CLASS_COUNTER, &mpi_t_manager);
  performance_vars_->addPerformanceVariable(tmp_p);

  tmp_p = new MVAPICHPerformanceVariable("mv2_smp_write_progress_poll_success", MPI_T_PVAR_CLASS_COUNTER, &mpi_t_manager);
  performance_vars_->addPerformanceVariable(tmp_p);
  
  int np;
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  tmp_p = new ConstantPerformanceVar("num_procs",(double)np);
  performance_vars_->addPerformanceVariable(tmp_p);
  
  return performance_vars_;
}
  
CollectionControlVar *CollectionCreatorMVAPICH::createCollectionControlVar()
{
    control_vars_ = new CollectionControlVar("MVAPICH","2.3");

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

  tmp = new MVAPICHBoolControlVariable("MPIR_CVAR_USE_RDMA_CM", &mpi_t_manager);
  control_vars_->addControlVariable(tmp);
  
  tmp = new MVAPICHBoolControlVariable("MPIR_CVAR_CH3_ENABLE_HCOLL", &mpi_t_manager);
  control_vars_->addControlVariable(tmp);

  tmp = new MVAPICHIntControlVariable("MPIR_CVAR_CH3_RMA_OP_PIGGYBACK_LOCK_DATA_SIZE", 1024, &mpi_t_manager);
  control_vars_->addControlVariable(tmp);

  tmp = new MVAPICHIntControlVariable("MPIR_CVAR_POLLS_BEFORE_YIELD", 10, &mpi_t_manager);
  control_vars_->addControlVariable(tmp);

  tmp = new MVAPICHIntControlVariable("MPIR_CVAR_CH3_EAGER_MAX_MSG_SIZE", 1024, &mpi_t_manager);
  control_vars_->addControlVariable(tmp);

  return control_vars_;
}

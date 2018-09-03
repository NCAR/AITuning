#include <iostream>
#include "MPI_T_Obj.h"
#include "Probes.h"
#include "mpi.h"
#include "MPICH/Variables.h"

using namespace std;

int main(void)
{
  int provided;
  MPI_T_Manager mpi_t_manager;

  mpi_t_manager.initialize_MPI_T();
  MPI_Init_thread(NULL,NULL,MPI_THREAD_FUNNELED,&provided);

  MPICHIntControlVariable eager_limit("MPIR_CVAR_CH3_EAGER_MAX_MSG_SIZE", 128, &mpi_t_manager);

  eager_limit.printVar();
  
  return 0;
}

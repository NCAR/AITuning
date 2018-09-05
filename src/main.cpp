#include <iostream>
#include "MPI_T_Obj.h"
#include "Probes.h"
#include "mpi.h"
#include "MPICH/Variables.h"

using namespace std;

int main(void)
{
  int provided;
  
  MPI_Init_thread(NULL,NULL,MPI_THREAD_FUNNELED,&provided);
  
  return 0;
}

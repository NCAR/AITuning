#include "mpi.h"
#include <string>
#include <iostream>
#include <time.h>
#include "Probes.h"
#include "Variables.h"
#include "Controller.h"

using namespace std;

double start_time, start_get, start_put, start_collective, start_barrier;
static int n_procs, my_id;

static SingleProbe *total_time_p;
static SingleProbe *put_time_p;
static SingleProbe *get_time_p;
static SingleProbe *flush_time_p;

int MPI_Init_thread(int *argc, char ***argv, int required, int *provided)
{
  int provided_t, err = -1;
  bool async_on = false;

  AITuning_start("MPICH");

  err = PMPI_Init_thread(argc, argv, required, provided);

  MPI_Comm_size(MPI_COMM_WORLD, &n_procs);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

  if(my_id == 0)
    {
      UserDefinedPerformanceVar *total_time_v = new UserDefinedPerformanceVar((char*)"total_time",(char*)"total_time_log.txt");
      AITuning_addUserDefinedPerformanceVar(total_time_v);
      total_time_p = new SingleProbe((char*)"total_time_probe", total_time_v);

      UserDefinedPerformanceVar *put_time_v = new UserDefinedPerformanceVar((char*)"put_time",(char*)"put_time_log.txt",0.001);
      AITuning_addUserDefinedPerformanceVar(put_time_v);
      put_time_p = new SingleProbe((char*)"put_time_probe", put_time_v);

      UserDefinedPerformanceVar *get_time_v = new UserDefinedPerformanceVar((char*)"get_time",(char*)"get_time_log.txt",0.001);
      AITuning_addUserDefinedPerformanceVar(get_time_v);
      get_time_p = new SingleProbe((char*)"get_time_probe", get_time_v);

      UserDefinedPerformanceVar *flush_time_v = new UserDefinedPerformanceVar((char*)"flush_time",(char*)"flush_time_log.txt",0.001);
      AITuning_addUserDefinedPerformanceVar(flush_time_v);
      flush_time_p = new SingleProbe((char*)"flush_time_probe", flush_time_v);
    }
  
  start_time = MPI_Wtime();
  
  return err;
}

int MPI_Put(const void *origin_addr, int origin_count, MPI_Datatype
            origin_datatype, int target_rank, MPI_Aint target_disp,
            int target_count, MPI_Datatype target_datatype, MPI_Win win)
{
  int ret;
  double start_time_put, end_time_put;

  start_time_put = MPI_Wtime();
  ret = PMPI_Put(origin_addr, origin_count, origin_datatype,
		 target_rank, target_disp, target_count,
		 target_datatype, win);
  end_time_put = MPI_Wtime();

  put_time_p->registerValue(end_time_put - start_time_put);
  
  return ret;
}

int MPI_Win_flush(int rank, MPI_Win win)
{
  int ret;
  double start_time_flush, end_time_flush;
  start_time_flush = MPI_Wtime();
  ret = PMPI_Win_flush(rank, win);
  end_time_flush = MPI_Wtime();

  flush_time_p->registerValue(end_time_flush - start_time_flush);
  
  return ret;
}

int MPI_Finalize(void){

  int err = -1;
  double end_time,average,total_time,elapsed_time;

  end_time = MPI_Wtime();

  elapsed_time = end_time - start_time;

  MPI_Reduce(&elapsed_time, &total_time, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  total_time = total_time/n_procs;

  if(my_id == 0)
    total_time_p->registerValue(total_time);

  err = PMPI_Finalize();
  
  return err;
}

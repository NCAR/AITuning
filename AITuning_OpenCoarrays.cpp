#include "mpi.h"
#include <string>
#include <iostream>
#include <time.h>
using namespace std;

double start_time, start_get, start_put, start_collective, start_barrier;
static int n_procs, my_id;
// vector<double> get_ops;
// vector<double> put_ops;

MPI_T_cvar_handle async_h;
MPI_T_cvar_handle polls_h;
MPI_T_cvar_handle hcoll_h;
MPI_T_cvar_handle bulk_connect_h;

static void set_handler_bulk_connect()
{
  int cidx,nvals,err;
  err = MPI_T_cvar_get_index("MPIR_CVAR_NEMESIS_MXM_BULK_CONNECT",&cidx);
  if(err != MPI_SUCCESS)
    printf("Error in get index\n");
  err = MPI_T_cvar_handle_alloc(cidx, NULL, &bulk_connect_h, &nvals);
  if(err != MPI_SUCCESS)
    printf("Error in handle alloc\n");
}

static void set_handler_async()
{
  int cidx,nvals,err;
  err = MPI_T_cvar_get_index("MPIR_CVAR_ASYNC_PROGRESS",&cidx);
  if(err != MPI_SUCCESS)
    printf("Error in get index\n");
  err = MPI_T_cvar_handle_alloc(cidx, NULL, &async_h, &nvals);
  if(err != MPI_SUCCESS)
    printf("Error in handle alloc\n");
}

static void set_handler_hcoll()
{
  int cidx,nvals,err;
  err = MPI_T_cvar_get_index("MPIR_CVAR_CH3_ENABLE_HCOLL",&cidx);
  if(err != MPI_SUCCESS)
    printf("Error in get index\n");
  err = MPI_T_cvar_handle_alloc(cidx, NULL, &hcoll_h, &nvals);
  if(err != MPI_SUCCESS)
    printf("Error in handle alloc\n");
}

static void set_handler_polls()
{
  int cidx,nvals,err;
  err = MPI_T_cvar_get_index("MPIR_CVAR_POLLS_BEFORE_YIELD",&cidx);
  if(err != MPI_SUCCESS)
    printf("Error in get index\n");
  err = MPI_T_cvar_handle_alloc(cidx, NULL, &polls_h, &nvals);
  if(err != MPI_SUCCESS)
    printf("Error in handle alloc\n");
}

static void enable_bulk_connect()
{
  int enable = 1, value=-1, err = -1;
  err = MPI_T_cvar_write(bulk_connect_h, &enable);
}

static void enable_async()
{
  int enable = 1, value=-1, err = -1;
  err = MPI_T_cvar_write(async_h, &enable);
  // MPI_T_cvar_read(async_h,&value);
  // printf("New value %d\n",value);
  // if(err == MPI_T_ERR_CVAR_SET_NEVER)
  //   printf("Set NEVER\n");
  // if(err == MPI_T_ERR_CVAR_SET_NOT_NOW)
  //   printf("Set NOT NOW\n");
}

static void enable_hcoll()
{
  int enable = 1, value=-1, err = -1;
  err = MPI_T_cvar_write(hcoll_h, &enable);
}

static void disable_async()
{
  int disable = 0, value = -1;
  MPI_T_cvar_write(async_h, &disable);
}


int MPI_Init(int *argc, char ***argv){

  int provided, err = -1;
  bool async_on = false;

  MPI_T_init_thread(MPI_THREAD_MULTIPLE, &provided);
  set_handler_async();

  srand (time(NULL));
  
  if(rand() % 2)
    {
      async_on = true;
      //      enable_async();
      enable_hcoll();
    }

  err = PMPI_Init(argc, argv);

  MPI_Comm_size(MPI_COMM_WORLD, &n_procs);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
  
  if(async_on && my_id == 0)
    printf("Async on\n");

  start_time = MPI_Wtime();
  
  return err;
}


int MPI_Init_thread(int *argc, char ***argv, int required, int *provided)
{
  int provided_t, err = -1;
  bool async_on = false;

  MPI_T_init_thread(MPI_THREAD_MULTIPLE, &provided_t);
  set_handler_async();
  set_handler_hcoll();
  set_handler_bulk_connect();

  srand (time(NULL));
  
  if(rand() % 2)
    {
      async_on = true;
      //enable_async();
      //enable_hcoll();
      enable_bulk_connect();
      err = PMPI_Init_thread(argc, argv, MPI_THREAD_MULTIPLE, provided);
    }
  else
      err = PMPI_Init_thread(argc, argv, required, provided);
 

  MPI_Comm_size(MPI_COMM_WORLD, &n_procs);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

  if(async_on && my_id == 0)
    printf("Async on\n");
  
  start_time = MPI_Wtime();
  
  return err;
}

int MPI_Finalize(void){

  int err = -1;
  double end_time,average,total_time,elapsed_time;

  end_time = MPI_Wtime();

  elapsed_time = end_time - start_time;

  MPI_Reduce(&elapsed_time, &total_time, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  total_time = total_time/n_procs;

  if(my_id == 0)
    printf("Average elapsed_time: %lf\n",total_time);

  err = PMPI_Finalize();
  
  return err;
}

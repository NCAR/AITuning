#include <iostream>
#include <string>
#include <cstdio>
#include "mpi.h"

using namespace std;

class MPI_T_Manager
{
public:
  MPI_T_Manager();
  void initialize_MPI_T()
  {
    int provided = -1, thread_safety = MPI_THREAD_MULTIPLE;
    int err;

    err = MPI_T_init_thread(thread_safety, &provided);

    if(err != MPI_SUCCESS)
      perror ("Error during MPI_T_Init_thread");
  }

  MPI_T_cvar_handle getControlHandle(string control_var_name, int *cidx)
  {
    int err, nvals;
    MPI_T_cvar_handle c_handle;
    
    err = MPI_T_cvar_get_index(control_var_name, cidx);
    if(err != MPI_SUCCESS)
      perror ("Error during MPI_T_cvar_get_index");

    err = MPI_T_cvar_handle_alloc(*cidx, NULL, &c_handle, &nvals);
    if(err != MPI_SUCCESS)
      perror ("Error during handle allocation");

    return c_handle;
  }

  MPI_T_pvar_handle getPerformanceHandle(string performance_var_name)
  {
    int err, cidx, nvals;
    MPI_T_pvar_handle p_handle;
    
    err = MPI_T_pvar_get_index(performance_var_name, &cidx);
    if(err != MPI_SUCCESS)
      perror ("Error during MPI_T_pvar_get_index");

    err = MPI_T_pvar_handle_alloc(cidx, NULL, &p_handle, &nvals);
    if(err != MPI_SUCCESS)
      perror ("Error during handle allocation");

    return p_handle;
  }

  void onOffControlVar(MPI_T_cvar_handle c_handle, int onOff)
  {
    int err = -1;

    if(onOff == 0 || onOff == 1)
      {
	err = MPI_T_cvar_write(c_handle, &onOff);
	if(err != MPI_SUCCESS)
	  perror ("Error during cvar write");
      }
    else
      perror ("Wrong OnOff value");
  }

  template <class T>
  T getControlVar(MPI_T_cvar_handle c_handle)
  {
    int err = -1;
    T val;
    
    err = MPI_T_cvar_read(c_handle, &val);
    if(err != MPI_SUCCESS)
      perror ("Error during cvar read");

    return val;
  }

  template <class T>
  void setControlVar(MPI_T_cvar_handle c_handle, T val)
  {
    int err = -1;

    err = MPI_T_cvar_write(c_handle, &val);
    if(err != MPI_SUCCESS)
      perror ("Error during cvar write with value");
  }
  
};


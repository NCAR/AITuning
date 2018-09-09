#include <iostream>
#include <string>
#include <cstdio>
#include "MPI_T_Obj.h"
#include "mpi.h"

using namespace std;

MPI_T_Manager::MPI_T_Manager(){;}

void MPI_T_Manager::initialize_MPI_T()
  {
    int provided = -1, thread_safety = MPI_THREAD_FUNNELED;
    int err;

    err = MPI_T_init_thread(thread_safety, &provided);

    if(err != MPI_SUCCESS)
      perror ("Error during MPI_T_Init_thread");
  }

MPI_T_cvar_handle MPI_T_Manager::getControlHandle(string control_var_name, int *cidx)
  {
    int err, nvals;
    MPI_T_cvar_handle c_handle;
    
    err = MPI_T_cvar_get_index(control_var_name.c_str(), cidx);
    if(err != MPI_SUCCESS)
      perror ("Error during MPI_T_cvar_get_index");

    err = MPI_T_cvar_handle_alloc(*cidx, NULL, &c_handle, &nvals);
    if(err != MPI_SUCCESS)
      perror ("Error during handle allocation");

    return c_handle;
  }

MPI_T_pvar_session MPI_T_Manager::getPerformanceSession()
{
  MPI_T_pvar_session p_session;
  
  MPI_T_pvar_session_create(&p_session);
 
  return p_session;
}

MPI_T_pvar_handle MPI_T_Manager::getPerformanceHandle(string performance_var_name, int var_class, int *pidx, MPI_T_pvar_session p_session)
  {
    int err, nvals;
    MPI_T_pvar_handle p_handle;
    
    err = MPI_T_pvar_get_index(performance_var_name.c_str(), var_class, pidx);
    if(err != MPI_SUCCESS)
      perror ("Error during MPI_T_pvar_get_index");

    err = MPI_T_pvar_handle_alloc(p_session, *pidx, NULL, &p_handle, &nvals);
    if(err != MPI_SUCCESS)
      perror ("Error during p_handle allocation");

    return p_handle;
  }

void MPI_T_Manager::getPvarDatatype(int idx, MPI_Datatype *dt)
{
  int err = -1;

  err = MPI_T_pvar_get_info(idx, NULL, NULL, NULL, NULL, dt,
			    NULL, NULL, NULL, NULL, NULL, NULL,
			    NULL);
  if(err != MPI_SUCCESS)
    perror ("Error during MPI_T_pvar_get_info");
}

int MPI_T_Manager::getControlVar(MPI_T_cvar_handle c_handle)
  {
    int err = -1;
    int val;
    
    err = MPI_T_cvar_read(c_handle, &val);
    if(err != MPI_SUCCESS)
      perror ("Error during cvar read");

    return val;
  }

void MPI_T_Manager::setControlVar(MPI_T_cvar_handle c_handle, int val)
  {
    int err = -1;

    err = MPI_T_cvar_write(c_handle, &val);
    if(err != MPI_SUCCESS)
      perror ("Error during cvar write with value");
  }  

void MPI_T_Manager::onOffControlVar(MPI_T_cvar_handle c_handle, int onOff)
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

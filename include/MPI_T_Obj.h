#include <iostream>
#include <string>
#include <cstdio>
#include "mpi.h"

using namespace std;

#ifndef MPI_T_OBJ_H
#define MPI_T_OBJ_H

class MPI_T_Manager
{
public:
  MPI_T_Manager();
  void initialize_MPI_T();

  MPI_T_pvar_session getPerformanceSession();
  MPI_T_pvar_handle getPerformanceHandle(string performance_var_name, int var_class, int *pidx, MPI_T_pvar_session p_session);
  void getPvarDatatype(int, MPI_Datatype *);

  template <class T>
  T getPerformanceVar(MPI_T_pvar_session p_session, MPI_T_pvar_handle p_handle)
  {
    int err = -1;
    T res;
    
    err = MPI_T_pvar_read(p_session, p_handle, &res);
    if(err != MPI_SUCCESS)
      perror ("Error during MPI_T_pvar_read");
 
    return res;
  }

  
  MPI_T_cvar_handle getControlHandle(string, int *);
  void onOffControlVar(MPI_T_cvar_handle c_handle, int onOff);
  int getControlVar(MPI_T_cvar_handle c_handle);
  void setControlVar(MPI_T_cvar_handle c_handle, int val);
};
#endif

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

  MPI_T_cvar_handle getControlHandle(string, int *);

  void onOffControlVar(MPI_T_cvar_handle c_handle, int onOff);

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
#endif

#include <iostream>
#include <string>
#include "../Variables.h"
#include "MPI_T_Obj.h"
#include "mpi.h"

using namespace std;

#ifndef MVAPICH_VARS_H
#define MVAPICH_VARS_H

class MVAPICHPerformanceVariable : public PerformanceVariable
{
private:
  int index_;
  int var_class_;
  MPI_Datatype dt_;
  MPI_T_Manager *mpi_t_manager_ = NULL;
  MPI_T_pvar_handle p_handle_;
  MPI_T_pvar_session p_session_;
public:
  MVAPICHPerformanceVariable(string name, int var_class, MPI_T_Manager *mpi_t_manager);
  PerformanceVariableLog getPerformanceVariableLog();
  void logPerformanceValue();
  void saveLog();
};

class MVAPICHIntControlVariable : public ControlVariable
{
private:
  int index_;
  int value_; //Read from MPI_T
  int increment_;
  MPI_Datatype dt_;
  MPI_T_Manager *mpi_t_manager_ = NULL;
  MPI_T_cvar_handle c_handle;
public:
  MVAPICHIntControlVariable(string name, int inc, MPI_T_Manager *mpi_t_manager);
  int getValue();
  void setValue(int val);
  void setIncrement(int inc);
  void incrementVar();
  void decrementVar();
  void printVar();
};

class MVAPICHBoolControlVariable : public ControlVariable
{
private:
  int index_;
  int value_; //Read from MPI_T
  MPI_Datatype dt_;
  MPI_T_Manager *mpi_t_manager_ = NULL;
  MPI_T_cvar_handle c_handle;
public:
  MVAPICHBoolControlVariable(string name, MPI_T_Manager *mpi_t_manager);
  int getValue();
  void setValue(int val);
  void incrementVar();
  void decrementVar();
  void printVar();
};

#endif

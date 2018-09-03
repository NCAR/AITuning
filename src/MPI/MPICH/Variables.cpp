#include <iostream>
#include <string>
#include "mpi.h"

using namespace std;

class PerformanceVariableMPICH : public PerformanceVariable
{
private:
  string name_;
  int index_;
  int var_class_;
  MPI_Datatype dt_;
  MPI_T_Manager *mpi_t_manager_ = NULL;
public:

  PerformanceVariableMPICH(string name, int var_class, MPI_T_Manager *mpi_t_manager)
  {
    int err;
    name_ = name;
    mpi_t_manager_ = mpi_t_manager;
    var_class_ = var_class;
    err = MPI_T_pvar_get_index(name_, var_class_, &index_);
    if(err != MPI_SUCCESS)
      perror ("Error in PerformanceVariable Contructor");
  }
  
  PerformanceVariableLog getPerformanceVariableLog(){
    
  }

  void logPerformanceValue(double val){
    log_.logValue(val);
  }

  void saveLog(){
    ;
  }
};

class ControlVariableMPICHInt : public ControlVariable<int>
{
private:
  string name_;
  int index_;
  int value_; //Read from MPI_T
  int increment_;
  int var_class_;
  MPI_Datatype dt_;
  MPI_T_Manager *mpi_t_manager_ = NULL;
  MPI_T_cvar_handle c_handle;
public:

  ControlVariableMPICHInt(string name, int var_class, int inc, MPI_T_Manager *mpi_t_manager)
  {
    int err;
    name_ = name;
    increment_ = inc;
    mpi_t_manager_ = mpi_t_manager;
    var_class_ = var_class;
    c_handle = mpi_t_manager_->getControlHandle(name_, &index_);
    if(err != MPI_SUCCESS)
      perror ("Error in ControlVariable Contructor");
    value_ = mpi_t_manager->getControlVar(c_handle);
  }
  
  PerformanceVariableLog getPerformanceVariableLog(){
    
  }

  void logPerformanceValue(double val){
    log_.logValue(val);
  }

  void saveLog(){
    ;
  }
};

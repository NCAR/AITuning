#include <iostream>
#include <string>
#include "MPI_T_Obj.h"
#include "MVAPICH/Variables.h"
#include "mpi.h"

using namespace std;

PerformanceVariableMVAPICH::PerformanceVariableMVAPICH(string name, int var_class, MPI_T_Manager *mpi_t_manager)
{
  int err = -1;
  name_ = name;
  mpi_t_manager_ = mpi_t_manager;
  var_class_ = var_class;
  p_session_ = mpi_t_manager_->getPerformanceSession();
  p_handle_ = mpi_t_manager_->getPerformanceHandle(name_, var_class_, &index_, p_session_);
}

MVAPICHIntControlVariable::MVAPICHIntControlVariable(string name, int inc, MPI_T_Manager *mpi_t_manager)
{
  name_ = name;
  increment_ = inc;
  mpi_t_manager_ = mpi_t_manager;
  c_handle = mpi_t_manager_->getControlHandle(name_, &index_);
  value_ = mpi_t_manager_->getControlVar(c_handle);
}

int MVAPICHIntControlVariable::getValue()
{
  return value_;
}

void MVAPICHIntControlVariable::setValue(int val)
{
  mpi_t_manager_->setControlVar(c_handle, val);
  value_ = mpi_t_manager_->getControlVar(c_handle);
  if (value_ != val)
    perror("Set on control variable unsuccessful");
}

void MVAPICHIntControlVariable::setIncrement(int inc)
{
  increment_ = inc;
}

void MVAPICHIntControlVariable::incrementVar()
{
  int new_val = -1;
  new_val = value_ + increment_;
  setValue(new_val);
}

void MVAPICHIntControlVariable::printVar()
{
  printf("%s: %d\n",name_.c_str(),value_);
}

MVAPICHBoolControlVariable::MVAPICHBoolControlVariable(string name, MPI_T_Manager *mpi_t_manager)
{
  name_ = name;
  mpi_t_manager_ = mpi_t_manager;
  c_handle = mpi_t_manager_->getControlHandle(name_, &index_);
  if(c_handle == NULL)
    perror ("Error in ControlVariable Contructor");
  value_ = mpi_t_manager_->getControlVar(c_handle);
}

int MVAPICHBoolControlVariable::getValue()
{
  return value_;
}

void MVAPICHBoolControlVariable::setValue(int val)
{  
  mpi_t_manager_->setControlVar(c_handle, val == 0 ? 0 : 1);
  value_ = mpi_t_manager_->getControlVar(c_handle);
  if (value_ != val)
    perror("Set on control variable unsuccessful");
}

void MVAPICHBoolControlVariable::incrementVar()
{
  if(value_ == 1)
    {
      mpi_t_manager_->onOffControlVar(c_handle,0);
      value_ = 0;
    }
  else
    {
      mpi_t_manager_->onOffControlVar(c_handle,1);
      value_ = 1;
    }
}

void MVAPICHBoolControlVariable::printVar()
{
  printf("%s: %d\n",name_.c_str(),value_);
}

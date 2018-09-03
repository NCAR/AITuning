#include <iostream>
#include <string>
using namespace std;

class MPI_T_Performance_Manager mpi_t_manager;
{
  
};

class PerformanceVariableMPICH : public PerformanceVariable
{
  
public:

  PerformanceVariableMPICH(string name)
  {
    name_ = name;
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

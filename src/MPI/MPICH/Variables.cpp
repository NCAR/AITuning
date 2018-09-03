#include <iostream>
#include <string>
using namespace std;

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

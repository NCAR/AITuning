#include <iostream>
#include "Variables.h"
#include "Probes.h"

using namespace std;

class UDPerformanceVariable : public PerformanceVariable
{
public:
  UDPerformanceVariable(string name){
    name_ = name;
  }

  PerformanceVariableLog getPerformanceVariableLog()
  {
    return log_;
  }
 
  void logPerformanceValue(VariableValue val)
  {
    log_.logValue(val.getValue());
  }

  void saveLog()
  {
    cout<<"SAVE LOG"<<name_<<endl;
  }
   
};

int main(void)
{
  UDPerformanceVariable total_time("Time");
  VariableValue v;
  v.setValue(10);
  total_time.logPerformanceValue(v);
  PerformanceVariableLog log = total_time.getPerformanceVariableLog();
  log.printLastLog();
  return 0;
}

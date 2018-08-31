#include <iostream>
#include "Variables.h"
#include "Probes.h"

using namespace std;

class MPICHControlVarInt : public ControlVariable<int>
{
public:

  MPICHControlVarInt(string name, int inc)
  {
    name_ = name;
    value_ = 0; //Read from MPIT or file
    increment_ = inc;
  }

  void setControlVariable(int val)
  {
    value_ = val;
  }
  
  int getControlVariable()
  {
    return value_;
  }

  void setIncrement(int step)
  {
    increment_ = step;
  }

  void incrementVar()
  {
    value_ += increment_;
  }

  void printVar()
  {
    cout<<"ControlVariable: "<<name_<<" Value: "<<value_<<endl;
  }

};

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
 
  void logPerformanceValue(double val)
  {
    log_.logValue(val);
  }

  void saveLog()
  {
    cout<<"SAVE LOG"<<name_<<endl;
  }
   
};

int main(void)
{
  UDPerformanceVariable total_time("Time");
  MPICHControlVarInt eager_limit("MPIT_EAGER_LIMIT",100);
  double v = 10.0;
  total_time.logPerformanceValue(v);
  eager_limit.incrementVar();
  PerformanceVariableLog log = total_time.getPerformanceVariableLog();
  log.printLastLog();
  eager_limit.printVar();
  return 0;
}

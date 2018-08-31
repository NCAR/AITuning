#include <iostream>
#include <string>
using namespace std;

class VariableValue {
private:
  int value;
public:
  void setValue(int val);
  int getValue();
};

class PerformanceVariableLog {
  
};

// Abstract class
class ControlVariable
{
private:
  string name;
  VariableValue value;
  int increment;
public:
  virtual void setControlVariable(VariableValue);
  virtual VariableValue getControlVariable();
};

class PerformanceVariableOpenMPI
{
public:

  PerformanceVariableOpenMPI(string name)
  {
    name_ = name;
    log_ = new PerformanceVariableLog();
  }
  
  PerformanceVariableLog getPerformanceVariableLog(){

  }
  void logPerformanceValue(VariableValue){

  }
  void saveLog(){

  }
};

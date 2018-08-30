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

// Abstract class
class PerformanceVariable
{
private:
  string name;
  PerformanceVariableLog log;
public:
  virtual logPerformanceValue();
  virtual PerformanceVariableLog getPerformanceVariableLog();
  virtual void registerValue(VariableValue);
  virtual void saveLog();
};

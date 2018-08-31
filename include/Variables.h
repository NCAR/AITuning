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
private:
  int last_log;
  std::vector<float> recent_log;
  std::map<int,vector> history_log;
public:
  
};

// Abstract class
class ControlVariable
{
private:
  string name_;
  VariableValue value_;
  int increment_;
public:
  virtual void setControlVariable(VariableValue);
  virtual VariableValue getControlVariable();
};

// Abstract class
class PerformanceVariable
{
private:
  string name_;
  PerformanceVariableLog log_;
public:
  virtual PerformanceVariableLog getPerformanceVariableLog();
  virtual void logPerformanceValue(VariableValue);
  virtual void saveLog();
};
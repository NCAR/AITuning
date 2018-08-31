#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#ifndef VARIABLES_H
#define VARIABLES_H

class VariableValue {
private:
  int value_;
public:
  VariableValue(){;}
  VariableValue(int v)
  {
    setValue(v);
  }
  void setValue(int val)
  {
    value_ = val;
  }
  int getValue()
  {
    return value_;
  }
};

class PerformanceVariableLog {
private:
  int last_log_;
  std::vector<int> recent_log_;
  std::map<int,std::vector<int>> history_log_;
public:
  PerformanceVariableLog(){last_log_ = 0;}
  void logValue(int val)
  {
    recent_log_.push_back(val);
  }
  void printLastLog()
  {
    cout << recent_log_.back() << endl;
  }
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
protected:
  string name_;
  PerformanceVariableLog log_;
public:
  virtual PerformanceVariableLog getPerformanceVariableLog() = 0;
  virtual void logPerformanceValue(VariableValue val) = 0;
  virtual void saveLog() = 0;
};

#endif

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#ifndef VARIABLES_H
#define VARIABLES_H

class VariableValue {
private:
  double value_;
public:
  VariableValue(){;}
  VariableValue(double v)
  {
    setValue(v);
  }

  void setValue(double val)
  {
    value_ = val;
  }
  
  double getValue()
  {
    return value_;
  }
};

class PerformanceVariableLog {
private:
  int last_log_;
  std::vector<double> recent_log_;
  std::map<int,std::vector<double>> history_log_;
public:
  PerformanceVariableLog(){last_log_ = 0;}
  void logValue(double val)
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

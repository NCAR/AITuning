#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#ifndef VARIABLES_H
#define VARIABLES_H

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
template <class Value>
class ControlVariable
{
protected:
  string name_;
  Value value_;
  int increment_;
public:
  ControlVariable(){;}
  virtual void setControlVariable(Value) = 0;
  virtual Value getControlVariable() = 0;
  virtual void setIncrement(int) = 0;
  virtual void incrementVar() = 0;
  virtual void printVar() = 0;
};

// Abstract class
class PerformanceVariable
{
protected:
  string name_;
  PerformanceVariableLog log_;
public:
  string getName(){
    return name_;
  }
  virtual PerformanceVariableLog getPerformanceVariableLog() = 0;
  virtual void logPerformanceValue(double val) = 0;
  virtual void saveLog() = 0;
};

#endif

#include <iostream>
#include <string>
#include <Serializable_Log.hpp>

using namespace std;

#ifndef VARIABLES_H
#define VARIABLES_H

// Abstract class
template <class Value>
class ControlVariable
{
protected:
  string name_;
  Value value_;
public:
  ControlVariable(){;}
  virtual void setValue(Value) = 0;
  virtual Value getValue() = 0;
  virtual void incrementVar() = 0;
  virtual void printVar() = 0;
};

class PerformanceVariable
{
protected:
  string name_;
  PerformanceVariableLog *log_;
public:

  PerformanceVariable(string name){
    name_ = name;
    log_ = new PerformanceVariableLog(name);
  }
  
  string getName(){
    return name_;
  }

  PerformanceVariableLog *getPerformanceVariableLog()
  {
    return log_;
  }
  
  void logPerformanceValue(double val)
  {
    log_->logValue(val);
  }
  
  void saveLog()
  {
    log_->saveHistory();
  }

  void loadLog()
  {
    log_->loadHistory();
  }
};

class UserDefinedPerformanceVariable : public PerformanceVariable
{
public:
  UserDefinedControlVariable(string filename);
};

#endif

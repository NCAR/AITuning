#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <fstream>
using namespace std;

#ifndef SERIAL_LOG_H
#define SERIAL_LOG_H

class PerformanceVariableLog {
private:
  string filename_;
  int last_log_;
  std::vector<double> recent_log_;
  std::vector<std::vector<double>> history_log_;    
public:
  
  PerformanceVariableLog(string filename)
  {
    last_log_ = 0;
    filename_ = filename;
  }
  
  void logValue(double val)
  {
    recent_log_.push_back(val);
  }
  
  void printLastLog()
  {
    cout << recent_log_.back() << endl;
  }

  double getLastLog()
  {
    return recent_log_.back();
  }

  void saveHistory()
  {
    std::ofstream outfile (filename_,std::ios::out | std::ios::app);
    for(std::vector<double>::iterator it = recent_log_.begin(); it != recent_log_.end(); ++it) {
      outfile << it << std::endl;
    }
    outfile.close();
  }

  void loadHistory()
  {
    // std::ifstream ifs( filename_ );
    // boost::archive::text_iarchive ar( ifs );
    // ar & history_log_;
    
    last_log_ = history_log_.size() - 1;
    recent_log_ = history_log_.back();
    history_log_.pop_back();
  }
};
#endif

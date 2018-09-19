#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

#ifndef STATISTICS_H
#define STATISTICS_H

class Statistics{
private:
  string var_name_;
  double min_ = 0.0;
  double max_ = 0.0;
  double mean_ = 0.0;
  double median_ = 0.0;
  vector<double> data_;
public:
  Statistics(string var_name, PerformanceVariableLog *log){
    var_name_ = var_name;
    data_ = log->getRecentLog();
  }

  string getName()
  {
    return var_name_;
  }

  double getMin()
  {
    if(min_ > 0.0)
      return min_;
    if(data_.size() == 0)
      return 0.0;
    min_ = *min_element(data_.begin(), data_.end());
    return min_;
  }

  double getMax()
  {
    if(max_ > 0.0)
      return max_;
    if(data_.size() == 0)
      return 0.0;
    max_ = *max_element(data_.begin(), data_.end());
    return max_;
  }

  double getMean()
  {
    if(mean_ > 0.0)
      return mean_;
    int size_data = data_.size();
    if(size_data == 0)
      return 0.d;
    double sum = std::accumulate(data_.begin(), data_.end(), 0.0);
    mean_ = sum / size_data;
    return mean_;
  }

  double getMedian()
  {
    int size_data = data_.size();
    if(median_ > 0.0)
      return median_;
    
    sort(data_.begin(), data_.end());
    if (size_data % 2 == 0)
      median_ =  (data_[size_data / 2 - 1] + data_[size_data / 2]) / 2;
    else 
      median_ = data_[size_data / 2];
    return median_;
  }
  
};
#endif

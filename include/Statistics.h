#include <iostream>
#include <vector>
#include <numeric>

class Statistics{
private:
  double min_;
  double max_;
  double mean_;
  double median_;
public:
  Statistics(PerformanceVariableLog log){
    vector<double> data = log->getRecentLog();
    int size_data = data.size();
    double sum = std::accumulate(data.begin(), data.end(), 0.0);

    mean_ = sum / size_data;
    min_ = std::min_element(data.begin(), data.end());
    max_ = std::max_element(data.begin(), data.end());

    sort(data.begin(), data.end());
    if (size_data % 2 == 0)
      median_ =  (data[size_data / 2 - 1] + data[size_data / 2]) / 2;
    else 
      median_ = data[size_data / 2];
  }

  
  
};

#ifndef ORDERPROCESSOR_H
#define ORDERPROCESSOR_H

#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <string>
#include <thread>
using namespace std;

class OrderProcessor {
public:
  OrderProcessor(const string &orderName)
      : orderName_(orderName), rndEngine_(random_device{}()) {}

  void operator()() {
    {
      lock_guard<mutex> lock(mutex_);
      cout << "Processing " << orderName_ << "\n";
    }

    uniform_int_distribution<int> dist(100, 200);
    this_thread::sleep_for(chrono::milliseconds(dist(rndEngine_)));

    {
      lock_guard<mutex> lock(mutex_);
      cout << "Completed " << orderName_ << "\n";
    }
  }

private:
  string orderName_;
  mt19937 rndEngine_;
  static mutex mutex_;
};

mutex OrderProcessor::mutex_;

#endif

int main() {
  thread t1(OrderProcessor("order1"));
  thread t2(OrderProcessor("order2"));
  t1.join();
  t2.join();
  cout << "All orders completed" << "\n";
  return 0;
}

#ifndef PHOTOGRAPHER_H
#define PHOTOGRAPHER_H

#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <string>
#include <thread>
using namespace std;

class Photographer {
public:
  Photographer(const string &celebrityName)
      : celebrityName_(celebrityName), rndEngine_(random_device{}()) {}

  void operator()() {
    {
      lock_guard<mutex> lock(mutex_);
      cout << "Capturing image of " << celebrityName_ << "\n";
    }

    uniform_int_distribution<int> dist(100, 200);
    this_thread::sleep_for(chrono::milliseconds(dist(rndEngine_)));

    {
      lock_guard<mutex> lock(mutex_);
      cout << "Completed image capture of " << celebrityName_ << "\n";
    }
  }

private:
  string celebrityName_;
  mt19937 rndEngine_;
  static mutex mutex_;
};

mutex Photographer::mutex_;

#endif

int main() {
  thread t1([]() {
    for (int i = 0; i < 5; ++i) {
      Photographer("Celeb 1")();
    }
  });
  thread t2([]() {
    for (int i = 0; i < 5; ++i) {
      Photographer("Celeb 2")();
    }
  });
  t1.join();
  t2.join();
  cout << "All image captures completed" << "\n";
  return 0;
}

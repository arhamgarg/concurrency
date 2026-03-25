#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <string>
#include <thread>
using namespace std;

class Downloader {
public:
  Downloader(const string &fileName)
      : fileName_(fileName), rndEngine_(random_device{}()) {}

  void operator()() {
    {
      lock_guard<mutex> lock(mutex_);
      cout << "Downloading " << fileName_ << "\n";
    }

    uniform_int_distribution<int> dist(100, 200);
    this_thread::sleep_for(chrono::milliseconds(dist(rndEngine_)));

    {
      lock_guard<mutex> lock(mutex_);
      cout << "Completed " << fileName_ << "\n";
    }
  }

private:
  string fileName_;
  mt19937 rndEngine_;
  static mutex mutex_;
};

mutex Downloader::mutex_;

#endif

int main() {
  thread t1(Downloader("file1.txt"));
  thread t2(Downloader("file2.txt"));
  t1.join();
  t2.join();
  cout << "All downloads completed" << "\n";
  return 0;
}

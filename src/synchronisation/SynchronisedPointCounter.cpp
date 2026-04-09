#ifndef SYNCHRONISEDPOINTCOUNTER_H
#define SYNCHRONISEDPOINTCOUNTER_H

#include <atomic>
using namespace std;

class SynchronisedPointCounter {
public:
  void increment() { points_.fetch_add(1, memory_order_relaxed); }

  int getPoints() const { return points_.load(memory_order_relaxed); }

private:
  atomic<int> points_{0};
};

#endif

#include <iostream>
#include <thread>

int main() {
  SynchronisedPointCounter counter;
  thread dancer1([&counter]() {
    for (int i = 0; i < 1000; ++i) {
      counter.increment();
    }
  });
  thread dancer2([&counter]() {
    for (int i = 0; i < 1000; ++i) {
      counter.increment();
    }
  });
  dancer1.join();
  dancer2.join();
  cout << "Total points: " << counter.getPoints() << endl;
  return 0;
}

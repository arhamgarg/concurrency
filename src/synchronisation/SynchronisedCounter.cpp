#ifndef SYNCHRONISEDCOUNTER_H
#define SYNCHRONISEDCOUNTER_H

#include <atomic>
using namespace std;

class SynchronisedCounter {
public:
  void incrementBy(int value) { count_.fetch_add(value, memory_order_relaxed); }

  int getCount() const { return count_.load(memory_order_relaxed); }

private:
  atomic<int> count_{0};
};

#endif

#include <iostream>
#include <thread>

int main() {
  SynchronisedCounter counter;
  thread t1([&counter]() {
    for (int i = 0; i < 1000; ++i) {
      counter.incrementBy(2);
    }
  });
  thread t2([&counter]() {
    for (int i = 0; i < 1000; ++i) {
      counter.incrementBy(2);
    }
  });
  t1.join();
  t2.join();
  cout << "Final count: " << counter.getCount() << "\n";
  return 0;
}

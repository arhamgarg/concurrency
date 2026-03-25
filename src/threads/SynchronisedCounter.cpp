#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

class SynchronisedCounter {
public:
  void increment() {
    lock_guard<mutex> lock(mutex_);
    count_++;
  }

  int getCount() const {
    lock_guard<mutex> lock(mutex_);
    return count_;
  }

private:
  mutable mutex mutex_;
  int count_ = 0;
};

int main() {
  SynchronisedCounter counter;
  thread t1([&counter]() {
    for (int i = 0; i < 10000; ++i)
      counter.increment();
  });
  thread t2([&counter]() {
    for (int i = 0; i < 10000; ++i)
      counter.increment();
  });
  t1.join();
  t2.join();
  cout << "Final count with synchronisation: " << counter.getCount() << "\n";
  return 0;
}

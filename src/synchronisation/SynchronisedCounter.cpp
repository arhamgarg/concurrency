#include <atomic>
#include <iostream>
#include <thread>
using namespace std;

class SynchronisedCounter {
public:
  void increment() { count_.fetch_add(1, memory_order_relaxed); }

  int getCount() const { return count_.load(memory_order_relaxed); }

private:
  atomic<int> count_{0};
};

int main() {
  SynchronisedCounter counter;
  thread t1([&counter]() {
    for (int i = 0; i < 1000; ++i)
      counter.increment();
  });
  thread t2([&counter]() {
    for (int i = 0; i < 1000; ++i)
      counter.increment();
  });
  t1.join();
  t2.join();
  cout << "Final count: " << counter.getCount() << "\n";
  return 0;
}

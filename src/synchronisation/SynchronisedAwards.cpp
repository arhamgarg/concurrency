#ifndef SYNCHRONISEDAWARDS_H
#define SYNCHRONISEDAWARDS_H

#include <atomic>
using namespace std;

class SynchronisedAwards {
public:
  void giveAward() { awards_.fetch_add(1, memory_order_relaxed); }

  int getAwards() { return awards_.load(memory_order_relaxed); }

private:
  atomic<int> awards_{0};
};

#endif

#include <iostream>
#include <thread>

int main() {
  SynchronisedAwards awards;
  thread vocalist([&awards]() {
    for (int i = 0; i < 1000; ++i) {
      awards.giveAward();
    }
  });
  thread guitarist([&awards]() {
    for (int i = 0; i < 1000; ++i) {
      awards.giveAward();
    }
  });
  vocalist.join();
  guitarist.join();
  cout << "Total awards: " << awards.getAwards() << "\n";
  return 0;
}

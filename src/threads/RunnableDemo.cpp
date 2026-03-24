#include <iostream>
#include <string>
#include <thread>
using namespace std;

class RunnableDemo {
public:
  RunnableDemo(const string &name) : threadName(name) {}

  void operator()() const { cout << "Running " << threadName << "\n"; }

private:
  string threadName;
};

int main() {
  thread t1(RunnableDemo("Thread 1"));
  thread t2(RunnableDemo("Thread 2"));
  thread t3([]() {
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "Lambda thread\n";
  });
  t1.join();
  t2.join();
  t3.detach();
  // t3.join(); // Error: Cannot join a detached thread

  cout << "End\n";
  this_thread::sleep_for(chrono::milliseconds(1000));

  return 0;
}

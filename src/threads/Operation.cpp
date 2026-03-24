#include <iostream>
#include <string>
#include <thread>
using namespace std;

class TaskExecutor {
public:
  TaskExecutor(const string &taskName) : taskName(taskName) {}

  void operator()() const { cout << "Executing " << taskName << "\n"; }

private:
  string taskName;
};

int main() {
  thread t1(TaskExecutor("Task 1"));
  thread t2(TaskExecutor("Task 2"));
  thread t3([]() {
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "Lambda Executing\n";
  });
  t1.join();
  t2.join();
  t3.detach();

  cout << "Execution Complete\n";
  this_thread::sleep_for(chrono::milliseconds(1000));

  return 0;
}

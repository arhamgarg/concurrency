#include <iostream>
#include <string>
#include <thread>
using namespace std;

class Operation {
public:
  Operation(const string &name) : threadName(name) {}

  void operator()() const { cout << "Running " << threadName << "\n"; }

private:
  string threadName;
};

int main() {
  thread t1(Operation("Find"));
  thread t2(Operation("Replace"));
  thread t3([]() {
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "Lambda thread executing\n";
  });
  t1.join();
  t2.join();
  t3.detach();

  cout << "End of main thread\n";
  this_thread::sleep_for(chrono::milliseconds(1000));

  return 0;
}

#include <iostream>
#include <thread>
using namespace std;

void hello() { cout << "Hello from a thread!\n"; }

int main() {
  thread t(hello);
  t.join();
  return 0;
}

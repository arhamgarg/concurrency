#include <iostream>
#include <string>
#include <thread>
using namespace std;

void hello(string msg) { cout << msg << "\n"; }

int main() {
  thread t(hello, "Hello from the superhero universe!");
  t.join();
  return 0;
}

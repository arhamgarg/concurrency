#include <iostream>
#include <string>
#include <thread>
using namespace std;

void displayMessage(const string &message) { cout << message << "\n"; }

int main() {
  string heroMessage = "Hello from the superhero universe!";
  thread t(displayMessage, heroMessage);
  t.join();
  return 0;
}

#ifndef MESSAGESENDER_H
#define MESSAGESENDER_H

#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <string>
#include <thread>
using namespace std;

class MessageSender {
public:
  MessageSender(const string &messageType)
      : messageType_(messageType), rndEngine_(random_device{}()) {}

  void operator()() {
    {
      lock_guard<mutex> lock(mutex_);
      cout << "Sending message: " << messageType_ << "\n";
    }

    uniform_int_distribution<int> dist(50, 150);
    this_thread::sleep_for(chrono::milliseconds(dist(rndEngine_)));

    {
      lock_guard<mutex> lock(mutex_);
      cout << "Message sent: " << messageType_ << "\n";
    }
  }

private:
  string messageType_;
  mt19937 rndEngine_;
  static mutex mutex_;
};

mutex MessageSender::mutex_;

#endif

int main() {
  thread t1(MessageSender("SMS"));
  thread t2(MessageSender("Email"));
  t1.join();
  t2.join();
  cout << "All messages sent" << "\n";
  return 0;
}

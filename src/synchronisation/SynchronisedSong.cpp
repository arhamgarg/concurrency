#ifndef SYNCHRONISEDSONG_H
#define SYNCHRONISEDSONG_H

#include <atomic>
using namespace std;

class SynchronisedSong {
public:
  void play() { playCount_.fetch_add(1, memory_order_relaxed); }

  int getPlayCount() { return playCount_.load(memory_order_relaxed); }

private:
  atomic<int> playCount_{0};
};

#endif

#include <iostream>
#include <thread>

int main() {
  SynchronisedSong song;
  thread user1([&song]() {
    for (int i = 0; i < 500; ++i) {
      song.play();
    }
  });
  thread user2([&song]() {
    for (int i = 0; i < 500; ++i) {
      song.play();
    }
  });
  user1.join();
  user2.join();
  cout << "Total play count: " << song.getPlayCount() << "\n";
  return 0;
}

#include <iostream>
#include "stopwatch.cpp"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void unisleep(unsigned int seconds) {
#ifdef _WIN32
  Sleep(seconds);
#else
  sleep(seconds);
#endif
}

Stopwatch some_function(Stopwatch sw) {
  std::cout << sw.milliseconds() << '\n';
  sw.stop();
  unisleep(1);
  std::cout << sw.seconds() << '\n';
  sw.resume();
  unisleep(1);
  std::cout << sw.milliseconds() << '\n';

  return sw;
}

int main() {
  Stopwatch sw;

  std::cout << sw.milliseconds() << '\n'; // ~0 milliseconds

  sw.start();
  unisleep(1);
  std::cout << sw.seconds() << '\n'; // 1 second

  unisleep(1);
  sw.stop();
  std::cout << sw.milliseconds() << '\n'; // 2000 milliseconds

  unisleep(1);

  sw.resume();
  unisleep(1);
  std::cout << sw.milliseconds() << '\n'; // 3000 milliseconds

  sw = some_function(sw);

  unisleep(1);
  sw.stop();
  std::cout << sw.milliseconds() << '\n';
  std::cout << sw.counter.count() << '\n';

  return 0;
}


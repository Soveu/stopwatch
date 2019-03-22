#include <chrono>

struct Stopwatch {
  using ClockType    = std::chrono::high_resolution_clock;
  using Milliseconds = std::chrono::duration<double, std::milli>;
  using Seconds      = std::chrono::duration<double>;

  ClockType::time_point timePoint;
  ClockType::duration   counter   = ClockType::duration::zero();
  bool                  isStopped = true;

  void start() {
    this->timePoint = ClockType::now();
    this->counter   = ClockType::duration::zero();
    this->isStopped = false;
  }

  void stop() {
    this->counter += (ClockType::now() - this->timePoint);
    this->isStopped = true;
  }

  void resume() {
    if(!this->isStopped) {
      return;
    }

    this->timePoint = ClockType::now();
    this->isStopped = false;
  }

  double milliseconds() const {
    if(this->isStopped) {
      return Milliseconds(this->counter).count();
    }

    return Milliseconds(ClockType::now() - this->timePoint + this->counter).count();
  }

  double seconds() const {
    if(this->isStopped) {
      return Seconds(this->counter).count();
    }
  
    return Seconds(ClockType::now() - this->timePoint + this->counter).count();
  }
};


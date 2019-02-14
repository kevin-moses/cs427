#include "task.hpp"

#include <string>
#include <iostream>

namespace todo
{
  Task::Task(const std::string& d, int t) : description{d}
  {
    estimatedTime = t;
    completed = false;
  }

  void Task::complete()
  {
    completed = true;
  }

  bool Task::isCompleted() const
  {
    return completed;
  }

  void Task::print(std::ostream& os) const
  {
    os << estimatedTime << " " << description;
  }

  int Task::time() const
  {
    return estimatedTime;
  }

  std::ostream& operator<<(std::ostream& os, const Task& t)
  {
    t.print(os);
    return os;
  }

}
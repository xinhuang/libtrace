#pragma once

#include <string>

namespace perf {

class Task {
  const std::string Name;

public:
  Task(std::string &&Name) : Name(std::move(Name)) {}

  const std::string &getName() const { return Name; }
};
}

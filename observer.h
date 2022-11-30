#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

class Observer {
public:
  virtual ~Observer() = default;
  virtual void notify(string gameResult) = 0;
};

#endif

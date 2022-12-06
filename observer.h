#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

using namespace std;

class Observer {
public:
  virtual ~Observer() = default;
  virtual void notify(string gameResult) = 0;
};

#endif

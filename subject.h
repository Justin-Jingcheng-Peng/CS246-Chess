#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <string>
#include "observer.h"

class Observer;

class Subject
{
  std::vector<Observer *> observers;

public:
  Subject();
  void attach(Observer *o);
  void detach(Observer *o);
  void notifyObservers(std::string result);
  virtual ~Subject() = default;
};

#endif

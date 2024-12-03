#pragma once
#include "components.hpp"

// Setter sets a variable to a value or another variable within the data
class Setter : public ComplexComponent {
public:
  Setter(string id, string newVar, string newVal);
  ~Setter();

  int inputFunction(ComponentData d) = 0;
  int process();

protected:
  string var, val;
};

class VariableSetter : public Setter {
public:
  VariableSetter(string id, string newVar, string newVal);
  ~VariableSetter();

  int inputFunction(ComponentData d);
};

class ValueSetter : public Setter {
public:
  ValueSetter(string id, string newVar, string newVal);
  ~ValueSetter();

  int inputFunction(ComponentData d);
};

#include "components.hpp"
#include <iostream>

using std::cout;
using std::endl;

// Setter class implementation
Setter::Setter(string id, string newVar, string newVal)
    : Component(id), var(newVar), val(newVal) {
  printf("Setter created\n");
}

Setter::~Setter() { printf("Setter destroyed\n"); }

int Setter::inputFunction(ComponentData d) {
  // This function is pure virtual in the base class
  return 0;
}

int Setter::process() { return 0; }

// VariableSetter class implementation
VariableSetter::VariableSetter(string id, string newVar, string newVal)
    : Setter(id, newVar, newVal) {
  printf("VariableSetter created\n");
}

VariableSetter::~VariableSetter() { printf("VariableSetter destroyed\n"); }

int VariableSetter::inputFunction(ComponentData d) {
  cout << "Setting " << var << " from " << val << endl;
  if (d.find(val) != d.end()) {
    d[var] = d[val];
  }

  for (auto output : getOutputs()) {
    output->inputFunction(d);
  }

  return 0;
}

// ValueSetter class implementation
ValueSetter::ValueSetter(string id, string newVar, string newVal)
    : Setter(id, newVar, newVal) {
  printf("ValueSetter created\n");
}

ValueSetter::~ValueSetter() { printf("ValueSetter destroyed\n"); }

int ValueSetter::inputFunction(ComponentData d) {
  cout << "Setting " << var << " to " << val << endl;
  d[var] = val;

  for (auto output : getOutputs()) {
    output->inputFunction(d);
  }

  return 0;
}
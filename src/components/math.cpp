#include "components.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::to_string;

// Adder class implementation
Adder::Adder(string id) : Component(id) { printf("Adder created\n"); }

Adder::~Adder() { printf("Adder destroyed\n"); }

int Adder::inputFunction(ComponentData d) {
  cout << "Adding " << d["a"] << " and " << d["b"] << endl;
  int a = stoi(d["a"]);
  int b = stoi(d["b"]);
  int sum = a + b;
  d["a"] = to_string(sum);

  for (auto output : getOutputs()) {
    output->inputFunction(d);
  }

  return 0;
}

int Adder::process() { return 0; }

// Subtractor class implementation
Subtractor::Subtractor(string id) : Component(id) {
  printf("Subtractor created\n");
}

Subtractor::~Subtractor() { printf("Subtractor destroyed\n"); }

int Subtractor::inputFunction(ComponentData d) {
  cout << "Subtracting " << d["a"] << " and " << d["b"] << endl;
  int a = stoi(d["a"]);
  int b = stoi(d["b"]);
  int sum = a - b;
  d["a"] = to_string(sum);

  for (auto output : getOutputs()) {
    output->inputFunction(d);
  }

  return 0;
}

int Subtractor::process() { return 0; }

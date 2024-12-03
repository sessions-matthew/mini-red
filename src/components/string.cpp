#include "components.hpp"
#include <iostream>

using std::cout;
using std::endl;

// Implementation of Concatenator methods
Concatenator::Concatenator(string id) : Component(id) {
  printf("Concatenator created\n");
}

Concatenator::~Concatenator() { printf("Concatenator destroyed\n"); }

int Concatenator::inputFunction(ComponentData d) {
  cout << "Concatenating " << d["payload"] << " and " << d["concat"] << endl;
  d["payload"] = d["payload"] + d["concat"];
  d.erase("concat");

  for (auto output : getOutputs()) {
    output->inputFunction(d);
  }

  return 0;
}

int Concatenator::process() { return 0; }

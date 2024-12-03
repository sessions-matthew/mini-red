#pragma once
#include "components.hpp"

// Adder adds two numbers
class Adder : public ComplexComponent {
public:
  Adder(string id);
  ~Adder();

  int inputFunction(ComponentData d);
  int process();
};

// Subtractor subtracts two numbers
class Subtractor : public ComplexComponent {
public:
  Subtractor(string id);
  ~Subtractor();

  int inputFunction(ComponentData d);
  int process();
};

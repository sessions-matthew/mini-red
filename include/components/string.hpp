#pragma once
#include "components.hpp"

// Concatenator concatenates two strings
class Concatenator : public ComplexComponent {
public:
  Concatenator(string id);
  ~Concatenator();

  int inputFunction(ComponentData d);
  int process();
};

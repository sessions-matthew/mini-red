#pragma once

// only compile on Linux
#ifdef __linux__
#include <string>
#include "components.hpp"

class BleComponent : public ComplexComponent {

public:
  BleComponent(string id);
  ~BleComponent();

  void init();
  int process();
  int inputFunction(ComponentData d);
};

#endif
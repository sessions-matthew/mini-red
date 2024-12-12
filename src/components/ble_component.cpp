#include "components/ble_component.hpp"

// only compile on Linux
#ifdef __linux__
BleComponent::BleComponent(string id) : ComplexComponent(id) {}

BleComponent::~BleComponent() { printf("BleComponent destroyed\n"); }

void BleComponent::init() {
  printf("BleComponent initialized\n");
}

int BleComponent::process() {
  printf("BleComponent processed\n");
  return 0;
}

int BleComponent::inputFunction(ComponentData d) {
  printf("BleComponent received data\n");
  return 0;
}

#endif
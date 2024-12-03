#include "components.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

#include <random>

// Function to calculate a checksum of a string
ChecksumType makeChecksum(const string &str) {
  ChecksumType hash = 0;
  for (char c : str) {
    hash = c + (hash << 6) + (hash << 16) - hash;
  }
  return hash;
}

// Component class implementation
Component::Component() : id(""), checksum(0) {}

Component::Component(string id) : id(id), checksum(0) {
  setChecksum(makeChecksum(id));
}

void Component::setId(string newId) { id = newId; }

string &Component::getId() { return id; }

void Component::setChecksum(ChecksumType newChecksum) {
  checksum = newChecksum;
}

ChecksumType Component::getChecksum() const { return checksum; }

// OutputComponent class implementation
OutputComponent::OutputComponent() : input(nullptr) {
  input = new ComponentQueue();
}

OutputComponent::~OutputComponent() { printf("Component destroyed\n"); }

ComponentQueue *OutputComponent::getInput() const { return input; }

// InputComponent class implementation
InputComponent::InputComponent() : outputs() {}

InputComponent::~InputComponent() {}

void InputComponent::addOutput(OutputComponent *newOutput) {
  if (newOutput == nullptr) {
    return;
  }
  if (find_if(outputs.begin(), outputs.end(), [&newOutput](OutputComponent *a) {
        return newOutput->getId() == a->getId();
      }) != outputs.end()) {
    return;
  }
  outputs.push_back(newOutput);
}

void InputComponent::removeOutput(OutputComponent *output) {
  outputs.erase(remove_if(outputs.begin(), outputs.end(),
                          [&output](OutputComponent *a) {
                            return output->getId() == a->getId();
                          }),
                outputs.end());
}

ComponentOutputs InputComponent::getOutputs() const { return outputs; }

// ComplexComponent class implementation
ComplexComponent::ComplexComponent() {}

// Implementation of Trigger class functions
Trigger::Trigger(string id) : Component(id) { printf("Trigger created\n"); }

Trigger::~Trigger() { printf("Trigger destroyed\n"); }

int Trigger::process() {
  if (lastTime == 0) {
    lastTime = time(nullptr);
  }
  if (time(nullptr) - lastTime > 1) {
    lastTime = time(nullptr);
    ComponentData data;
    data["a"] = "1";
    data["b"] = "2";
    data["payload"] = "Hello, world!";
    data["topic"] = "test";
    for (auto output : getOutputs()) {
      output->inputFunction(data);
    }
    return 1;
  }
  return 0;
}

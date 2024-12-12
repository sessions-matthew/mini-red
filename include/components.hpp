#pragma once
#include <map>
#include <queue>
#include <string>
#include <vector>

using std::map;
using std::queue;
using std::string;
using std::vector;

class OutputComponent;
class InputComponent;

using ComponentData = map<string, string>;
using ComponentQueue = queue<ComponentData>;
using ComponentOutputs = vector<OutputComponent *>;
using ChecksumType = unsigned int;

ChecksumType makeChecksum(const string &str);

class Component {
protected:
  string id;
  ChecksumType checksum;

public:
  void setChecksum(ChecksumType newChecksum);
  ChecksumType getChecksum() const;
  void setId(string newId);
  string &getId();
  virtual ~Component() = default;
  Component();
  Component(string id);
};

// Type of component that can consume data
class OutputComponent : public virtual Component {
  ComponentQueue *input;

public:
  OutputComponent();
  ~OutputComponent();
  ComponentQueue *getInput() const;
  virtual int inputFunction(ComponentData d) = 0;
};

// Type of component that can create data
class InputComponent : public virtual Component {
  ComponentOutputs outputs;

public:
  InputComponent();
  ~InputComponent();
  void addOutput(OutputComponent *newOutput);
  void removeOutput(OutputComponent *output);
  ComponentOutputs getOutputs() const;
};

// Type of component that can consume and create data
class ComplexComponent : public virtual InputComponent,
                         public virtual OutputComponent {
public:
  ComplexComponent();
};

// Trigger creates an event at every cycle
class Trigger : public InputComponent {
  unsigned long lastTime;
public:
  Trigger(string id);
  ~Trigger();

  int process();
};

#include "components/setter.hpp"
#include "components/math.hpp"
#include "components/io.hpp"
#include "components/javascript.hpp"
#include "components/string.hpp"
#include "components/mqtt_component.hpp"
#include "components/ble_component.hpp"
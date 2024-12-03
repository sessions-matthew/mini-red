#pragma once
#include "components.hpp"
#include "mqtt.hpp"
#include <mutex>

// MqttComponent is the base class for MqttInputComponent and
// MqttOutputComponent
class MqttComponent : public virtual Component {
public:
  MqttComponent(string id);
  void init(string host, int port, string client_id, string username,
            string password);

protected:
  Mqtt::Session session;
  ~MqttComponent();
};

// MqttInputComponent subscribes to a topic and sends the data to its outputs
class MqttInputComponent : public MqttComponent, public InputComponent {
  queue<ComponentData> data_queue;
  mutex data_queue_mutex;

public:
  MqttInputComponent(string id);
  void init(string host, int port, string client_id, string username,
            string password, string topic);
  int process();
  ~MqttInputComponent();
};

// MqttOutputComponent publishes the data it receives to the mqtt broker
class MqttOutputComponent : public MqttComponent, public ComplexComponent {
  queue<ComponentData> data_queue_out;
  mutex data_queue_out_mutex;

public:
  MqttOutputComponent(string id);
  int inputFunction(ComponentData d);
  int process();
  ~MqttOutputComponent();
};

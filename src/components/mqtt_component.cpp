#include "components.hpp"
#include <thread>

MqttComponent::MqttComponent(string id) : Component(id) {}

void MqttComponent::init(string host, int port, string client_id,
                         string username, string password) {
  session.init(host, port, client_id, username, password);
}

MqttComponent::~MqttComponent() { printf("MqttComponent destroyed\n"); }

MqttInputComponent::MqttInputComponent(string id) : MqttComponent(id) {}

void MqttInputComponent::init(string host, int port, string client_id,
                              string username, string password, string topic) {

  MqttComponent::init(host, port, client_id, username, password);
  session.subscribe(topic, 0, 1);

  std::thread([this, topic]() {
    while (true) {
      session.handleSocket();
      if (!session.pub_incoming_queue.empty()) {
        auto publish = session.pub_incoming_queue.front();
        session.pub_incoming_queue.pop();
        ComponentData data;
        data["topic"] = publish.topic;
        data["payload"] = publish.message;
        data_queue_mutex.lock();
        data_queue.push(data);
        data_queue_mutex.unlock();
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  }).detach();
}

int MqttInputComponent::process() {
  data_queue_mutex.lock();
  while (!data_queue.empty()) {
    auto data = data_queue.front();
    data_queue.pop();
    data_queue_mutex.unlock();
    for (auto output : getOutputs()) {
      output->inputFunction(data);
    }
    data_queue_mutex.lock();
  }
  data_queue_mutex.unlock();
  return 0;
}

MqttInputComponent::~MqttInputComponent() {
  printf("MqttComponent destroyed\n");
}

MqttOutputComponent::MqttOutputComponent(string id) : MqttComponent(id) {
  std::thread([this]() {
    while (true) {
      session.handleSocket();
      data_queue_out_mutex.lock();
      if (!data_queue_out.empty()) {
        auto data = data_queue_out.front();
        data_queue_out.pop();
        session.publish(data["topic"], data["payload"], 0, false);
      }
      data_queue_out_mutex.unlock();
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  }).detach();
}

int MqttOutputComponent::inputFunction(ComponentData d) {
  data_queue_out_mutex.lock();
  data_queue_out.push(d);
  data_queue_out_mutex.unlock();
  return 0;
}

int MqttOutputComponent::process() { return 0; }

MqttOutputComponent::~MqttOutputComponent() {
  printf("MqttComponent destroyed\n");
}
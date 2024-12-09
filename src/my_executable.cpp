#include "duktape.h"
#include "mqtt.hpp"
#include <fstream>
#include <iostream>
#include <json.hpp>
#include <map>
#include <queue>
#include <stdio.h>
#include <string>

#include "components.hpp"

using namespace std;
using nlohmann::json;

struct Parameter {
  string name;
  string valueStr;
  int valueInt;
  string type;
};

struct Line {
  string start;
  string end;
};

void from_json(const json &j, Parameter &p) {
  j.at("name").get_to(p.name);
  if (j.at("value").is_string()) {
    j.at("value").get_to(p.valueStr);
  } else {
    j.at("value").get_to(p.valueInt);
  }
  j.at("type").get_to(p.type);
}

void from_json(const json &j, Line &l) {
  j.at("start").get_to(l.start);
  j.at("end").get_to(l.end);
}

int main() {
  ifstream file("../program.json");
  json j = nlohmann::json::parse(file);
  vector<function<int()>> processors;
  map<string, Component *> componentsById;

  auto &generated = j["generated"];

  auto &components = generated["components"];
  if (components.empty()) {
    cout << "No components found" << endl;
    return 1;
  }
  cout << "Components found" << endl;

  auto &lines = generated["lines"];
  if (lines.empty()) {
    cout << "No lines found" << endl;
    return 1;
  }
  cout << "Lines found" << endl;

  for (auto &component : components) {
    cout << "===============================" << endl;
    string id = component["id"];
    string type = component["type"];
    map<string, Parameter> parameters;
    if (component.find("parameters") != component.end() &&
        component["parameters"].is_array()) {
      for (auto &parameter : component["parameters"].get<vector<Parameter>>()) {
        parameters[parameter.name] = parameter;
      }
    }
    cout << "Component: " << id << " of type " << type << " with "
         << parameters.size() << " parameters" << endl;
    if (type == "Trigger") {
      Trigger *trigger = new Trigger(id);
      componentsById[id] = trigger;
      cout << "Address: " << trigger << endl;
      processors.push_back(bind(&Trigger::process, trigger));
    } else if (type == "Logger") {
      string prefix = "";
      if (parameters.find("Prefix") != parameters.end()) {
        prefix = parameters["Prefix"].valueStr;
      }
      Logger *logger = new Logger(id, prefix);
      componentsById[id] = logger;
      processors.push_back(bind(&Logger::process, logger));
    } else if (type == "MqttIn") {
      string host = parameters["Host"].valueStr;
      int port = parameters["Port"].valueInt;
      string clientId = parameters["ClientId"].valueStr;
      string username = parameters["Username"].valueStr;
      string password = parameters["Password"].valueStr;
      string topic = parameters["Topic"].valueStr;
      MqttInputComponent *mqttInput = new MqttInputComponent(id);
      componentsById[id] = mqttInput;
      mqttInput->init(host, port, clientId, username, password, topic);
      processors.push_back(bind(&MqttInputComponent::process, mqttInput));
    } else if (type == "MqttOut") {
      string host = parameters["Host"].valueStr;
      int port = parameters["Port"].valueInt;
      string clientId = parameters["ClientId"].valueStr;
      string username = parameters["Username"].valueStr;
      string password = parameters["Password"].valueStr;
      MqttOutputComponent *mqttOutput = new MqttOutputComponent(id);
      componentsById[id] = mqttOutput;
      mqttOutput->init(host, port, clientId, username, password);
      processors.push_back(bind(&MqttOutputComponent::process, mqttOutput));
    } else if (type == "Script") {
      string code = parameters["Expression"].valueStr;
      JavascriptCode *script = new JavascriptCode(id);
      componentsById[id] = script;
      cout << "Initializing script with:" << code << endl;
      cout << "Script: " << script->getId() << endl;
      cout << "ID: " << id << endl;
      cout << "Address: " << script << endl;
      script->init(code);
      processors.push_back(bind(&JavascriptCode::process, script));
    }
  }

  for (auto &line : lines.get<vector<Line>>()) {
    cout << "= = = = = = = = = = = = = = = " << endl;
    cout << "Connecting " << line.start << " to " << line.end << endl;
    if (componentsById.find(line.start) != componentsById.end() &&
        componentsById.find(line.end) != componentsById.end()) {
      auto inputComponent =
          dynamic_cast<InputComponent *>(componentsById[line.start]);
      auto outputComponent =
          dynamic_cast<OutputComponent *>(componentsById[line.end]);
      if (inputComponent != nullptr && outputComponent != nullptr) {
        inputComponent->addOutput(outputComponent);
      } else {
        cout << "Component not found for: " << line.start << " to " << line.end
             << endl;
      }
    } else {
      cout << "Component not found" << endl;
    }
  }

  cout << ">>> Main loop starting" << endl;
  for (;;) {
    int msgs = 0;
    for (auto processor : processors) {
      msgs += processor();
    }
    if (msgs == 0) {
      usleep(100000);
    }
  }

  return 0;
}

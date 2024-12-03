#pragma once
#include "duktape.h"
#include "components.hpp"

// JavascriptComponent is a base class for components that use javascript
class JavascriptComponent : public virtual Component {
protected:
  duk_context *ctx;

public:
  JavascriptComponent();
  ~JavascriptComponent();
};

class JavascriptSetter : public Setter, public JavascriptComponent {
public:
  JavascriptSetter(string id, string newVar, string newVal);
  ~JavascriptSetter();

  int inputFunction(ComponentData d);
};

class Router : public ComplexComponent, public JavascriptComponent {
  vector<string> conditions;
  vector<OutputComponent *> routes;

public:
  Router(string id);
  ~Router();

  int inputFunction(ComponentData d);
  int init(vector<string> conditions, vector<OutputComponent *> routes);
  int process();
};

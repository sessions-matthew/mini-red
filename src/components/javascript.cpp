#include "components.hpp"
#include "duktape.h"
#include <iostream>

using std::cerr;
using std::endl;

JavascriptComponent::JavascriptComponent() {
  printf("JavascriptComponent created\n");
  ctx = duk_create_heap_default();
  if (!ctx) {
    cerr << "Failed to create a Duktape heap." << endl;
    exit(1);
  }
}

JavascriptComponent::~JavascriptComponent() {
  printf("JavascriptComponent destroyed\n");
  if (ctx) {
    duk_destroy_heap(ctx);
  }
}

JavascriptSetter::JavascriptSetter(string id, string newVar, string newVal)
    : Setter(id, newVar, newVal) {
  printf("JavascriptSetter created\n");
}

JavascriptSetter::~JavascriptSetter() {
  printf("JavascriptSetter destroyed\n");
}

int JavascriptSetter::inputFunction(ComponentData d) {
  duk_push_global_object(ctx);
  duk_push_string(ctx, "set");
  duk_push_string(ctx, var.c_str());
  duk_push_string(ctx, val.c_str());
  duk_call_prop(ctx, -3, 2);
  duk_pop(ctx);

  for (auto output : getOutputs()) {
    output->inputFunction(d);
  }

  return 0;
}

Router::Router(string id) : Component(id) {
  printf("Router created\n");
}

Router::~Router() { printf("Router destroyed\n"); }

int Router::inputFunction(ComponentData d) {
  for (int i = 0; i < conditions.size(); i++) {
    duk_get_global_string(ctx, ("condition" + to_string(i)).c_str());
    duk_push_object(ctx);
    for (const auto &pair : d) {
      duk_push_string(ctx, pair.second.c_str());
      duk_put_prop_string(ctx, -2, pair.first.c_str());
    }
    duk_call(ctx, 1);

    if (duk_is_boolean(ctx, -1)) {
      if (duk_get_boolean(ctx, -1)) {
        routes[i]->inputFunction(d);
      }
    }
  }
  return 0;
}

int Router::init(vector<string> conditions, vector<OutputComponent *> routes) {
  cout << "Initializing router" << endl;

  this->conditions = conditions;
  this->routes = routes;

  for (int i = 0; i < conditions.size(); i++) {
    string &condition = conditions[i];
    string function = "function condition" + to_string(i) + " (msg) { return " +
                      condition + "; }";
    duk_eval_string(ctx, function.c_str());
  }
  return 0;
}

int Router::process() { return 0; }
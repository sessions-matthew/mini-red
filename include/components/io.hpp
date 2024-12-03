#pragma once
#include "components.hpp"

// Logger logs the data to the console
class Logger : public OutputComponent {
    string prefix;

public:
    Logger(string id, string prefix = "");
    ~Logger();

    int inputFunction(ComponentData d);
    int process();
};

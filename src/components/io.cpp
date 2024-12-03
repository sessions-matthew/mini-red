#include "components.hpp"

// Constructor
Logger::Logger(string id, string prefix) : Component(id), prefix(prefix) {
    printf("Logger created\n");
}

// Destructor
Logger::~Logger() {
    printf("Logger destroyed\n");
}

// inputFunction
int Logger::inputFunction(ComponentData d) {
    for (const auto &pair : d) {
        printf("%s%s: %s\n", prefix.c_str(), pair.first.c_str(),
                     pair.second.c_str());
    }
    return 0;
}

// process
int Logger::process() {
    return 0;
}
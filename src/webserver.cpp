#include "httplib.h"
#include <csignal>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <stdio.h>

httplib::Server svr;

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

pid_t pid = -1;

int main() {
  printf("Hello, Meson!\n");

  svr.Get("/hi", [](const httplib::Request &, httplib::Response &res) {
    res.set_content("Hello World!", "text/plain");
  });

  svr.Get("/download", [](const httplib::Request &, httplib::Response &res) {
    ifstream file("program.json");
    if (file.is_open()) {
      res.set_content(string((std::istreambuf_iterator<char>(file)),
                             std::istreambuf_iterator<char>()),
                      "application/json");
      file.close();
    } else {
      res.status = 500;
      res.set_content("Failed to open file", "text/plain");
    }
  });

  svr.Post("/upload", [](const httplib::Request &req, httplib::Response &res) {
    cout << req.body << endl;
    ofstream file("program.json");
    if (file.is_open()) {
      file << req.body;
      file.close();
      res.set_content("File uploaded successfully", "text/plain");
    } else {
      res.status = 500;
      res.set_content("Failed to open file", "text/plain");
    }
  });

  svr.Get("/start", [](const httplib::Request &, httplib::Response &res) {
    if (pid == -1) {
      pid = fork();
      if (pid == 0) {
        execlp("./builddir/my_executable", "./my_executable", nullptr);
        exit(0);
      }
      // check that fork succeeded
      if (pid == -1) {
        res.status = 500;
        res.set_content("{\"running\":false}", "text/plain");
      } else {
        res.set_content("{\"running\":true}", "text/plain");
      }
    } else {
      res.set_content("{\"running\":true}", "text/plain");
    }
  });

  svr.Get("/stop", [](const httplib::Request &, httplib::Response &res) {
    if (pid != -1) {
      kill(pid, SIGTERM);
      pid = -1;
      res.set_content("{\"running\":false}", "text/plain");
    } else {
      res.set_content("{\"running\":false}", "text/plain");
    }
  });

  svr.Get("/status", [](const httplib::Request &, httplib::Response &res) {
    if (pid != -1) {
      res.set_content("{\"running\":true}", "text/plain");
    } else {
      res.set_content("{\"running\":false}", "text/plain");
    }
  });

  svr.set_mount_point("/", "./public");

  svr.listen("0.0.0.0", 8080);

  return 0;
}

#include "httplib.h"
#include <functional>
#include <stdio.h>
#include <fstream>

httplib::Server svr;

using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::string;

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

  svr.set_mount_point("/", "./public");

  svr.listen("0.0.0.0", 8080);

  return 0;
}

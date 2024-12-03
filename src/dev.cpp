#include <functional>
#include <iostream>
#include <stdio.h>

#include <boost/asio/as_tuple.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/use_awaitable.hpp>

#include <boost/asio/detached.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "mqtt.hpp"

using namespace std;

int main() {
  cout << "TODO double check spec and make sure that variable size integers "
          "are being used correctly"
       << endl;
  cout << "TODO check for memory leaks" << endl;

  Mqtt::Session session;
  session.init("192.168.3.2", 1883, "client1", "hue", "hue2468");
  session.publish("testing/1", "hello world???", 0, false);
  session.subscribe("testing/1", 0, 1);

  Mqtt::Session session1;
  session1.init("192.168.3.2", 1883, "client2", "hue", "hue2468");

  while (true) {
    session1.publish("testing/1", "hello world", 0, false);

    sleep(1);
    session.handleSocket();
    session1.handleSocket();
  }

  sleep(1);
  return 0;
}

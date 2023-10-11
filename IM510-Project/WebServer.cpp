#include <snode.c/express/middleware/StaticMiddleware.h>

#include "WebServer.h"

WebServer::WebServer(int argc, char *argv[]) {
  express::legacy::in::WebApp::init(argc, argv);

  webApp = express::legacy::in::WebApp("legacy");

  initRoutes();
  listen();
}

int WebServer::start() { return express::WebApp::start(); }

bool WebServer::isLoggedIn() { return loggedInAs.length() > 0; }

std::string WebServer::getLoggedInUserName() { return loggedInAs; }

void WebServer::setLoggedInUserName(std::string username) {
  loggedInAs = username;
}

void WebServer::initRoutes() {
  forumController.initRoutes(*this);
  userController.initRoutes(*this);
  postController.initRoutes(*this);
  threadController.initRoutes(*this);
  topicController.initRoutes(*this);
}

void WebServer::listen() {
  using SocketAddress = express::legacy::in::WebApp::SocketAddress;
  webApp.listen(
      [](const SocketAddress &socketAddress, const core::socket::State &state)
          -> void { // Listen on all IPv4 interfaces on port 8001{
        switch (state) {
        case core::socket::State::OK:
          VLOG(1) << "in: listening on '" << socketAddress.toString() << "'";
          break;
        case core::socket::State::DISABLED:
          VLOG(1) << "in: disabled";
          break;
        case core::socket::State::ERROR:
          VLOG(1) << "in: non critical error occurred";
          break;
        case core::socket::State::FATAL:
          VLOG(1) << "in: critical error occurred";
          break;
        }
      });
}

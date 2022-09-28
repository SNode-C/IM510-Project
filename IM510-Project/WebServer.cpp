#include <snode.c/express/middleware/StaticMiddleware.h>

#include "WebServer.h"

WebServer::WebServer(int argc, char* argv[])
{
    express::legacy::in::WebApp::init(argc, argv);

    webApp = express::legacy::in::WebApp("legacy");

    initRoutes();
    listen();
}

int WebServer::start()
{
    return express::WebApp::start();
}

bool WebServer::isLoggedIn()
{
    return loggedInAs.length() > 0;
}

std::string WebServer::getLoggedInUserName()
{
    return loggedInAs;
}

void WebServer::setLoggedInUserName(std::string username)
{
    loggedInAs = username;
}

void WebServer::initRoutes()
{
    forumController.initRoutes(*this);
    userController.initRoutes(*this);
    postController.initRoutes(*this);
    threadController.initRoutes(*this);
    topicController.initRoutes(*this);
}

void WebServer::listen()
{
    webApp.listen([](const express::legacy::in::WebApp::SocketAddress &socketAddress,
        int err) -> void {
            if (err != 0) {
                PLOG(FATAL) << "listen on " << socketAddress.toString();
            } else {
                VLOG(0) << "snode.c listening on " << socketAddress.toString();
            }
        }
    );
}

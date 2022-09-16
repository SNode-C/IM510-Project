#include <snode.c/express/middleware/StaticMiddleware.h>

#include "WebServer.h"

WebServer::WebServer(int argc, char* argv[])
{
    express::legacy::in::WebApp::init(argc, argv);

    WebApp = express::legacy::in::WebApp("legacy");

    initRoutes();
    listen();
}

int WebServer::start()
{
    return express::WebApp::start();
}

void WebServer::initRoutes()
{
    WebApp.get("/", []APPLICATION(req, res) {
                      res.send("Hello World!");
                  });

    //legacyApp.use(express::middleware::StaticMiddleware("/home/student/dev/snode.c-doc/html"));
}

void WebServer::listen()
{
    WebApp.listen([](const express::legacy::in::WebApp::SocketAddress &socketAddress,
                        int err) -> void {
                        if (err != 0) {
                            PLOG(FATAL) << "listen on " << socketAddress.toString();
                        } else {
                            VLOG(0) << "snode.c listening on " << socketAddress.toString();
                        }
    });
}

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <snode.c/express/legacy/in/WebApp.h>

class WebServer
{
public:
    WebServer(int argc, char* argv[]);

    int start();

protected:
    express::legacy::in::WebApp WebApp;

    void initRoutes();
    void listen();
};

#endif // WEBSERVER_H

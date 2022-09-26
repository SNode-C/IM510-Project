#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <snode.c/express/legacy/in/WebApp.h>

#include "Database.h"
#include "loginpage.h"
#include "registerpage.h"
#include "forum.h"



class WebServer
{
public:
    WebServer(int argc, char* argv[]);
    RegisterPage registerPage;
    LoginPage loginPage;
    Forum forum;
    std::string loggedInAs = "";
    int start();
protected:
    express::legacy::in::WebApp webApp;
    Database database;

    void initRoutes();
    void listen();
};

#endif // WEBSERVER_H

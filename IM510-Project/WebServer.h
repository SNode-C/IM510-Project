#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <snode.c/express/legacy/in/WebApp.h>

#include "Database.h"

#include "UserController.h"
#include "ForumController.h"
#include "TopicController.h"
#include "ThreadController.h"
#include "PostController.h"

class WebServer
{
public:
    WebServer(int argc, char* argv[]);

    express::legacy::in::WebApp webApp;
    Database database;

    int start();
    bool isLoggedIn();
    std::string getLoggedInUserName();
    void setLoggedInUserName(std::string username);

protected:
    UserController userController;
    ForumController forumController;
    TopicController topicController;
    ThreadController threadController;
    PostController postController;

    std::string loggedInAs = "";

    void initRoutes();
    void listen();
};

#endif // WEBSERVER_H

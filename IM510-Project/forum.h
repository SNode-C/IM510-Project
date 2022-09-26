#ifndef FORUM_H
#define FORUM_H

#include <snode.c/express/legacy/in/WebApp.h>
#include <string>
#include "Database.h"
#include <chrono>

class Forum
{
public:
    Forum();
    void defineRoutes(express::legacy::in::WebApp &WebApp, Database &db, std::string &loggedInAs);

private:
    std::string topics ="";
    std::string threads ="";
    std::string posts ="";
};

#endif // FORUM_H



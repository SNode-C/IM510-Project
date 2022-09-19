#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <snode.c/express/legacy/in/WebApp.h>
#include <string>
#include "Database.h"


class LoginPage
{
public:
    LoginPage();
    std::string GetHTML();
    void defineRoutes(express::legacy::in::WebApp &WebApp, Database &db, std::string &loggedInAs);
    int found = 0;

private:
    std::string parseRequest(std::string &str, const std::string &keyword);
    bool isLogin(std::string& res);

};

#endif // LOGINPAGE_H



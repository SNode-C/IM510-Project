#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <snode.c/express/legacy/in/WebApp.h>
#include <string>
#include "Database.h"

class RegisterPage
{
public:
    RegisterPage();

    std::string GetHTML();
    int post(std::string body, express::legacy::in::WebApp &WebApp, Database &db);
    void defineRoutes(express::legacy::in::WebApp &WebApp, Database &db, std::string &loggedInAs);
    int success = 0;

private:

    std::string parseRequest(std::string &str, const std::string &keyword);
    bool isRegister(std::string& res);


};

#endif // REGISTERPAGE_H



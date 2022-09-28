#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <string>

#include "AbstractController.h"

class UserController : AbstractController
{
public:
    UserController();
    virtual void initRoutes(WebServer &webServer) override;

protected:
    int success = 0;
    int found = 0;

    std::string parseRequest(std::string &str, const std::string &keyword);
    bool isRegister(std::string& res);
    bool isLogin(std::string& res);
};

#endif // USERCONTROLLER_H

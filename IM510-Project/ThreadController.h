#ifndef THREADCONTROLLER_H
#define THREADCONTROLLER_H

#include <string>

#include "AbstractController.h"

class ThreadController : AbstractController
{
public:
    ThreadController();
    virtual void initRoutes(WebServer &webServer) override;

protected:
    std::string threads = "";
};

#endif // THREADCONTROLLER_H

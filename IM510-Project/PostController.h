#ifndef POSTCONTROLLER_H
#define POSTCONTROLLER_H

#include <string>

#include <snode.c/web/http/server/Request.h>

#include "AbstractController.h"

class PostController : AbstractController
{
public:
    PostController();
    virtual void initRoutes(WebServer &webServer) override;

protected:
    std::string posts = "";
    std::string currentUserId = "";
};

#endif // POSTCONTROLLER_H

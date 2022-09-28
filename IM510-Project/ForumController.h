#ifndef FORUMCONTROLLER_H
#define FORUMCONTROLLER_H

#include "AbstractController.h"

class ForumController : AbstractController
{
public:
    ForumController();
    virtual void initRoutes(WebServer &webServer) override;
};

#endif // FORUMCONTROLLER_H

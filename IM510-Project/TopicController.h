#ifndef TOPICCONTROLLER_H
#define TOPICCONTROLLER_H

#include <string>

#include "AbstractController.h"

class TopicController : AbstractController
{
public:
    TopicController();
    virtual void initRoutes(WebServer &webServer) override;

protected:
    std::string topics = "";
};

#endif // TOPICCONTROLLER_H

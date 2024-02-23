#ifndef ABSTRACTCONTROLLER_H
#define ABSTRACTCONTROLLER_H

#include <string>

#include <memory>
#include <snode.c/express/Request.h>

class WebServer;

class AbstractController {
public:
  AbstractController();
  virtual void initRoutes(WebServer &webServer) = 0;

  virtual std::string getParam(const std::shared_ptr<express::Request> req,
                               const std::string &key);
};

#endif // ABSTRACTCONTROLLER_H

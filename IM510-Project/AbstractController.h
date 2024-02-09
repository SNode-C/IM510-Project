#ifndef ABSTRACTCONTROLLER_H
#define ABSTRACTCONTROLLER_H

#include <string>

#include <memory>
#include <snode.c/web/http/server/Request.h>

class WebServer;

class AbstractController {
public:
  AbstractController();
  virtual void initRoutes(WebServer &webServer) = 0;

  virtual std::string getParam(std::shared_ptr<web::http::server::Request> req,
                               const std::string &key);
};

#endif // ABSTRACTCONTROLLER_H

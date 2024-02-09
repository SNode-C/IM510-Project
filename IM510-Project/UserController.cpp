#include "UserController.h"

#include "LoginHtmlProvider.h"
#include "RegisterHtmlProvider.h"
#include "WebServer.h"

UserController::UserController() {}

void UserController::initRoutes(WebServer &webServer) {
  // Log out user
  webServer.webApp.get("/logout", [this, &webServer] APPLICATION(req, res) {
    webServer.setLoggedInUserName("");
    res->redirect("/");
  });

  // Get form for registering a new user
  webServer.webApp.get("/register", [this] APPLICATION(req, res) {
    RegisterHtmlProvider registerPage;
    res->send(registerPage.getHtml());
  });

  // Register a new user
  webServer.webApp.post("/register", [this, &webServer] APPLICATION(req, res) {
    std::string body = "";
    body.assign(req->body.begin(), req->body.end());

    std::string userName = parseRequest(body, "uname");
    std::string email = parseRequest(body, "email");
    std::string password = parseRequest(body, "password");

    if (!isRegister(body)) {
      res->redirect("/");
      return;
    }

    if (userName.size() == 0 || email.size() == 0 || password.size() == 0) {
      webServer.setLoggedInUserName("");
      res->redirect("/register");
      return;
    }

    this->success = 1;

    webServer.database.mariadb.query(
        "SELECT * FROM `users`",
        [this, userName, email, password, &webServer,
         res](const MYSQL_ROW row) -> void { // Gets called for each row found.
          if (row != nullptr) {
            if (row[1] == userName) {
              this->success = 0;
            }
            if (row[2] == email) {
              this->success = 0;
            }
          } else {
            if (this->success == 1) {
              webServer.database.mariadb.exec(
                  "INSERT INTO `users`(`username`, `email`, `password`) VALUES "
                  "('" +
                      userName + "', '" + email + "', '" + password + "')",
                  [res, &webServer, userName]() -> void {
                    VLOG(0)
                        << "Query successful"; // num = affected rows I guess
                    webServer.setLoggedInUserName(userName);
                    res->redirect("/");
                  },
                  [](const std::string &errorString,
                     unsigned int errorNumber) -> void {
                    VLOG(0) << "Query failed 1: " << errorString << " : "
                            << errorNumber;
                  });
            } else {
              webServer.setLoggedInUserName("");
              res->redirect("/register");
            }
          }
        },
        [](const std::string &errorString, unsigned int errorNumber) -> void {
          VLOG(0) << "Query failed 2: " << errorString << " : " << errorNumber;
        });
  });

  // Get form for logging in
  webServer.webApp.get("/login", [this] APPLICATION(req, res) {
    LoginHtmlProvider loginPage;
    res->send(loginPage.getHtml());
  });

  // Log in user
  webServer.webApp.post("/login", [this, &webServer] APPLICATION(req, res) {
    found = 0;

    std::string body = "";
    body.assign(req->body.begin(), req->body.end());

    std::string userName = getParam(req, "uname");
    std::string password = getParam(req, "password");

    if (isLogin(body)) {
      if (userName.size() != 0 && password.size() != 0) {
        webServer.database.mariadb.query(
            "SELECT * FROM `users`",
            [this, userName, password, res, &webServer](const MYSQL_ROW row)
                -> void { // Gets called for each row found.
              if (row != nullptr) {
                if (row[1] == userName && row[3] == password) {
                  this->found = 1;
                  VLOG(0) << this->found;
                }
              } else {
                if (this->found == 1) {
                  webServer.setLoggedInUserName(userName);
                }
                res->redirect("/");
              }
            },
            [](const std::string &errorString,
               unsigned int errorNumber) -> void {
              VLOG(0) << "Query failed 3: " << errorString << " : "
                      << errorNumber;
            });
      } else {
        webServer.setLoggedInUserName("");
        res->redirect("/");
      }
    } else {
      res->redirect("/register");
    }
  });
}

// keyword is the thing that will be "cut out"
std::string UserController::parseRequest(std::string &str,
                                         const std::string &keyword) {
  int line = 0;
  int goalLine = 0;
  int nCount = 0;
  bool inRightLine = false;

  std::string newString = "";

  if (keyword == "uname") {
    goalLine = 3;
  } else if (keyword == "email") {
    goalLine = 7;
  } else if (keyword == "password") {
    goalLine = 11;
  }

  for (int i = 0; i < str.size(); i++) {
    if (inRightLine) {
      if (str[i] == '\r') {
        break;
      }

      newString = newString + str[i];
    } else {
      if (str[i] == '\n') {
        nCount++;
        if (nCount == goalLine) {
          inRightLine = true;
        }
      }
    }
  }

  return newString;
}

// depending on how many line breaks are in the response, we can determine
// whether or not it is a loginattempt
bool UserController::isRegister(std::string &res) {
  int count = 0;
  for (int i = 0; i < res.size(); i++) {
    if (res[i] == '\r') {
      count++;
    }
  }

  if (count > 3) {
    return true;
  }

  return false;
}

// depending on how many line breaks are in the response, we can determine
// whether or not it is a loginattempt
bool UserController::isLogin(std::string &res) {
  int count = 0;
  for (int i = 0; i < res.size(); i++) {
    if (res[i] == '\r') {
      count++;
    }
  }

  if (count > 3) {
    return true;
  }

  return false;
}

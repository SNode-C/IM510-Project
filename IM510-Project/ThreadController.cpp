#include "ThreadController.h"

#include "StyleHtmlProvider.h"
#include "WebServer.h"

ThreadController::ThreadController() {}

void ThreadController::initRoutes(WebServer &webServer) {
  // Get all threads of a topic
  webServer.webApp.get("/threads", [this, &webServer] APPLICATION(req, res) {
    std::string url = req.originalUrl;
    std::size_t pos = url.find("?");
    std::string currentTopicId = url.substr(pos + 1);
    // int currentTopicId = stoi(param);

    threads = "";

    std::string loggedInString = "Not logged in";
    if (webServer.isLoggedIn()) {
      loggedInString = "Logged in as: " + webServer.getLoggedInUserName();
    }

    webServer.database.mariadb.query(
        "SELECT thread.id, thread.name, thread.timestamp, users.username "
        "FROM `thread` "
        "INNER JOIN `users` ON thread.users__id=users.id "
        "WHERE thread.topic__id=" +
            currentTopicId,
        [this, &webServer, &res, currentTopicId,
         loggedInString](const MYSQL_ROW row) -> void {
          if (row != nullptr) {
            // Collect all threads
            threads = threads +
                      "<li class=\"row\">"
                      "<a href=\"posts?" +
                      std::string(row[0]) +
                      "\">"
                      "<h4 class=\"title\" >" +
                      std::string(row[1]) +
                      "</h4>"
                      "<div class=\"thread-info\">"
                      "<p class=\"timestamp\">" +
                      std::string(row[2]) + " by " + std::string(row[3]) +
                      "</p>"
                      "</div>"
                      "</a>"
                      "</li>"
                      "<hr>";

          } else {

            StyleHtmlProvider styleProvider;

            std::string buttonDisabledLoggedOff =
                webServer.isLoggedIn() ? "" : "disabled";
            std::string buttonDisabledLoggedIn =
                webServer.isLoggedIn() ? "disabled" : "";

            res.send("<div class=\"banner\">"
                     "<h1>"
                     "<a href=\"/\">Forum</a>"
                     " / Threads"
                     "</h1>"
                     "</div>"
                     "<div class=\"buttons\">"
                     "<a href=\"register\">"
                     "<button " +
                     buttonDisabledLoggedIn +
                     ">Register</button>"
                     "</a>"
                     "<a href=\"/login\">"
                     "<button " +
                     buttonDisabledLoggedIn +
                     ">Login</button>"
                     "</a>"
                     "<a href=\"/logout\">"
                     "<button " +
                     buttonDisabledLoggedOff +
                     ">Logout</button>"
                     "</a>"
                     "<a href=\"/createThread?topic__id=" +
                     currentTopicId +
                     "\">"
                     "<button " +
                     buttonDisabledLoggedOff +
                     ">Create Thread</button>"
                     "</a>" +
                     loggedInString +
                     "</div>"
                     "<div class=\"main\">"
                     "<ul><hr>" +
                     threads +
                     "</ul>"
                     "</div>" +
                     styleProvider.getHtml());
          }
        },
        [](const std::string &errorString, unsigned int errorNumber) -> void {
          VLOG(0) << "Query failed: " << errorString << " : " << errorNumber;
        });
  });

  // Get form for creating a new thread
  webServer.webApp.get("/createThread", [this, &webServer] APPLICATION(req,
                                                                       res) {
    std::string topicId = getParam(req, "topic__id");

    webServer.database.mariadb.query(
        "SELECT `id` FROM users WHERE `username` = '" +
            webServer.getLoggedInUserName() + "'",
        [&webServer, &res, topicId](const MYSQL_ROW row) -> void {
          if (row != nullptr) {
            StyleHtmlProvider styleProvider;

            res.send("<div class=\"banner\">"
                     "<h1>"
                     "<a href=\"/\">Forum</a> / Topic / Create Thread"
                     "</h1>"
                     "</div>"
                     "<div class=\"main\">"
                     "<div class=\"header\">"
                     "<h4 class=\"title\">Create a new thread!</h4>"
                     "</div>"
                     "<form method=\"post\" enctype=\"multipart/form-data\">"
                     "<input type=\"hidden\" name=\"users__id\" value=\"" +
                     std::string(row[0]) +
                     "\" />"
                     "<input type=\"hidden\" name=\"topic__id\" value=\"" +
                     topicId +
                     "\" />"
                     "<label for='name'>Title</label><br>"
                     "<input type='text' id='name' name='name'><br>"
                     "<button id='createThreadButton'>Create Thread</button>"
                     "</form>"
                     "</div>" +
                     styleProvider.getHtml());
          } else {
            VLOG(0) << "User not found.";
          }
        },
        [&res](const std::string &error, unsigned int errorNum) -> void {
          VLOG(0) << "User not found: " << error << ", " << errorNum << ".";
          res.redirect("/");
        });
  });

  // Create a new thread
  webServer.webApp.post(
      "/createThread", [this, &webServer] APPLICATION(req, res) {
        std::string threadName = getParam(req, "name");
        std::string userId = getParam(req, "users__id");
        std::string topicId = getParam(req, "topic__id");

        webServer.database.mariadb.exec(
            "INSERT INTO `thread`(`name`, `timestamp`, "
            "`users__id`,`topic__id`) VALUES('" +
                threadName + "', CURRENT_TIMESTAMP(), '" + userId + "', '" +
                topicId + "')",
            [&res]() -> void {
              VLOG(0) << "Thread added successfully.";
              res.redirect("/");
            },
            [&res](const std::string &error, unsigned int errorNum) -> void {
              VLOG(0) << "Adding new thread failed: " << error << ", "
                      << errorNum << ".";
              res.redirect("/");
            });
      });
}

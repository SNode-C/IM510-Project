#include <snode.c/database/mariadb/MariaDBCommandSequence.h>

#include "PostController.h"

#include "StyleHtmlProvider.h"
#include "WebServer.h"

PostController::PostController() {}

void PostController::initRoutes(WebServer &webServer) {
  // Get all posts of given thread
  webServer.webApp.get("/posts", [this, &webServer] APPLICATION(req, res) {
    std::string url = req->originalUrl;
    std::size_t pos = url.find("?");
    std::string threadId = url.substr(pos + 1);
    currentUserId = "";

    posts = "";

    webServer.database.mariadb
        .query(
            "SELECT `id` FROM `users` WHERE `username`= \"" +
                webServer.getLoggedInUserName() + "\"",
            [this, threadId](const MYSQL_ROW row) -> void {
              if (row != nullptr) {
                currentUserId = std::string(row[0]);
              }
            },
            [](const std::string &errorString,
               unsigned int errorNumber) -> void {
              VLOG(0) << "Query failed 6: " << errorString << " : "
                      << errorNumber;
            })
        .query(
            "SELECT post.text, post.timestamp, users.username, users.id "
            "FROM `post` "
            "INNER JOIN `users` ON post.users__id=users.id "
            "INNER JOIN `thread` ON post.thread__id=thread.id "
            "WHERE post.thread__id=" +
                threadId,
            [this, &webServer, res, threadId](const MYSQL_ROW row) -> void {
              if (row != nullptr) {
                // Collect all posts
                posts = posts +
                        "<div class=\"comment\" >"
                        "<div class=\"comment-info\">"
                        "<p class=\"user\">" +
                        std::string(row[2]) +
                        "</p>"
                        "<p class=\"comment-timestamp\">" +
                        std::string(row[1]) +
                        "</p>"
                        "</div>"
                        "<div class=\"comment-content\">" +
                        std::string(row[0]) +
                        "</div>"
                        "</div>";
              } else {
                StyleHtmlProvider styleProvider;

                std::string buttonDisabledLoggedOff =
                    webServer.isLoggedIn() ? "" : "disabled";
                std::string buttonDisabledLoggedIn =
                    webServer.isLoggedIn() ? "disabled" : "";

                std::string loggedInString = "Not logged in";
                if (webServer.isLoggedIn()) {
                  loggedInString =
                      "Logged in as: " + webServer.getLoggedInUserName();
                }

                res->send(
                    "<div class=\"banner\">"
                    "<h1>"
                    "<a href=\"/\">Forum</a>"
                    " / Threads / Posts"
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
                    "</a>" +
                    loggedInString +
                    "</div>"
                    "<div class=\"main\">"
                    "<div class=\"header\">"
                    "<h4 class=\"title\">"
                    "Thread Title"
                    "</h4>"
                    "</div>"
                    "<form action=\"/createPost\" method=\"post\" "
                    "enctype=\"multipart/form-data\">"
                    "<input type=\"hidden\" name=\"users__id\" value=\"" +
                    currentUserId +
                    "\" />"
                    "<input type=\"hidden\" name=\"thread__id\" value=\"" +
                    threadId +
                    "\" />"
                    "<textarea name=\"text\"></textarea><br>"
                    "<button " +
                    buttonDisabledLoggedOff +
                    ">Add post</button>"
                    "</form>"
                    "<div class=\"comments\">" +
                    posts +
                    "</div>"
                    "</div>" +
                    styleProvider.getHtml());
                VLOG(0) << "finish";
              }
            },
            [](const std::string &errorString,
               unsigned int errorNumber) -> void {
              VLOG(0) << "Query failed 7: " << errorString << " : "
                      << errorNumber;
            });
  });

  // Create new post
  webServer.webApp.post(
      "/createPost", [this, &webServer] APPLICATION(req, res) {
        std::string text = getParam(req, "text");
        std::string userId = getParam(req, "users__id");
        std::string threadId = getParam(req, "thread__id");

        webServer.database.mariadb.exec(
            "INSERT INTO `post`(`text`, `timestamp`, `users__id`,`thread__id`) "
            "VALUES('" +
                text + "', CURRENT_TIMESTAMP(), '" + userId + "', '" +
                threadId + "')",
            [res, threadId]() -> void {
              res->redirect("/posts?" + threadId);
              VLOG(0) << "Post added successfully.";
            },
            [](const std::string &error, unsigned int errorNum) -> void {
              VLOG(0) << "Adding new post failed: " << error << ", " << errorNum
                      << ".";
            });
      });
}

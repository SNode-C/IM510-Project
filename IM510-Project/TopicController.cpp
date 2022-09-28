#include "TopicController.h"

#include "WebServer.h"
#include "StyleHtmlProvider.h"

TopicController::TopicController()
{

}

void TopicController::initRoutes(WebServer &webServer)
{
    webServer.webApp.get("/topics", []APPLICATION(req, res) {
        res.redirect("/");
    });

    // Get form for creating a new topic
    webServer.webApp.get("/createTopic", [this, &webServer]APPLICATION(req, res) {
        webServer.database.mariadb.query(
            "SELECT `id` FROM `users` WHERE `username` = '" + webServer.getLoggedInUserName() + "'",
            [this, &webServer, &res](const MYSQL_ROW row) -> void {
                if (row != nullptr) {
                    VLOG(0) << "User found.";
                    StyleHtmlProvider styleProvider;

                    res.send(
                        "<div class=\"banner\">"
                            "<h1>"
                                "<a href=\"/\">Forum</a> / Create Topic"
                            "</h1>"
                        "</div>"
                        "<div class=\"main\">"
                            "<div class=\"header\">"
                                "<h4 class=\"title\">Create a new topic!</h4>"
                            "</div>"
                            "<form method=\"post\" enctype=\"multipart/form-data\">"
                                "<input type=\"hidden\" name=\"users__id\" value=\"" + std::string(row[0]) + "\" />"
                                "<label for='name'>Title</label><br>"
                                "<input type='text' id='name' name='name'><br>"
                                "<button id='createTopicButton'>Create Topic</button>"
                            "</form>"
                        "</div>"
                        + styleProvider.getHtml()
                    );
                } else {
                    VLOG(0) << "User not found.";
                }
            },
            [&res](const std::string &error, unsigned int errorNum) -> void {
                VLOG(0) << "User not found: " << error << ", " << errorNum << ".";
                res.redirect("/");
            }
        );
    });

    // Create a new topic
    webServer.webApp.post("/createTopic", [this, &webServer]APPLICATION(req, res) {
        std::string topicName = getParam(req, "name");
        std::string userId = getParam(req, "users__id");

        webServer.database.mariadb.exec(
            "INSERT INTO `topic`(`name`, `timestamp`, `users__id`) VALUES('" + topicName + "', CURRENT_TIMESTAMP(), '" + userId + "')",
            [&res](int num) -> void {
                VLOG(0) << "Topic added successfully.";
                res.redirect("/");
            },
            [&res](const std::string &error, unsigned int errorNum) -> void {
                VLOG(0) << "Adding new topic failed: " << error << ", " << errorNum << ".";
                res.redirect("/");
            }
        );
    });

    // Default route, show all topics
    webServer.webApp.get("/", [this, &webServer]APPLICATION(req, res) {

        topics="";

        std::string loggedInString = "Not logged in";
        if (webServer.isLoggedIn()) {
            loggedInString = "Logged in as: " + webServer.getLoggedInUserName();
        }

        webServer.database.mariadb.query(
            "SELECT * FROM `topic`",
            [this, &webServer, &res, loggedInString](const MYSQL_ROW row) -> void {
                if (row != nullptr) {
                    // Collect all topics
                    topics = topics +
                        "<li class=\"row\">"
                            "<a href=\"threads?" + std::string(row[0]) + "\">"
                                "<h4 class=\"title\" >"
                                    + std::string(row[1]) +
                                "</h4>"
                            "</a>"
                        "</li>"
                        "<hr>"
                        ;
                } else {

                    StyleHtmlProvider styleProvider;

                    std::string buttonDisabledLoggedOff = webServer.isLoggedIn() ? "" : "disabled";
                    std::string buttonDisabledLoggedIn = webServer.isLoggedIn() ? "disabled" : "";

                    res.send(
                        "<div class=\"banner\">"
                            "<h1>"
                                "<a href=\"/\">Forum</a>"
                                " / Topics"
                            "</h1>"
                        "</div>"
                        "<div class=\"buttons\">"
                            "<a href=\"register\">"
                                "<button " + buttonDisabledLoggedIn + ">Register</button>"
                            "</a>"
                            "<a href=\"/login\">"
                                "<button " + buttonDisabledLoggedIn + ">Login</button>"
                            "</a>"
                            "<a href=\"/logout\">"
                                "<button " + buttonDisabledLoggedOff + ">Logout</button>"
                            "</a>"
                            "<a href=\"/createTopic\">"
                                "<button " + buttonDisabledLoggedOff + ">Create Topic</button>"
                            "</a>"
                            "<a href=\"/addExamples\">"
                                "<button>Add example data to database</button>"
                            "</a>"
                            "<a href=\"/deleteAll\">"
                                "<button>Delete all data</button>"
                            "</a>"
                            + loggedInString +
                        "</div>"
                        "<div class=\"main\">"
                            "<ul><hr>"
                                + topics +
                            "</ul>"
                        "</div>"
                        + styleProvider.getHtml()
                    );
                }
            },
            [](const std::string& errorString, unsigned int errorNumber) -> void {
                VLOG(0) << "Query failed: " << errorString << " : " << errorNumber;
        });
    });
}

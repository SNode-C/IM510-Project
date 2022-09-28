#include "ForumController.h"

#include "WebServer.h"

ForumController::ForumController()
{

}

void ForumController::initRoutes(WebServer &webServer)
{
    // Add example data to database
    webServer.webApp.get("/addExamples", [this, &webServer]APPLICATION(req, res){

        webServer.database.mariadb.exec(
            "INSERT INTO `topic`(`id`, `name`, `timestamp`, `users__id`) VALUES "
            "(1, 'Topic #1', NOW(), '1'),"
            "(2, 'Lorem Ipsum', NOW(), '2'),"
            "(3, 'Dolor sit amet', NOW(), '3');",

            [&res](int num) -> void {
                VLOG(0) << "Query successful";
        },
            [](const std::string& errorString, unsigned int errorNumber) -> void {
                VLOG(0) << "Query failed: " << errorString << " : " << errorNumber;
        });

        webServer.database.mariadb.exec(
            "INSERT INTO `thread`(`id`, `name`, `timestamp`, `users__id`, `topic__id`) VALUES "   // remove ids?
            "(1, 'Lorem ipsum', NOW(), '1', '1'),"
            "(2, 'Dolor sit amet.', NOW(), '2', '2'),"
            "(3, 'Sed diam voluptua', NOW(), '4', '3'),"
            "(4, 'At vero eos et', NOW(), '5', '2'),"
            "(5, 'Sadipscing elitr, sed diam nonumy', NOW(), '1', '1'),"
            "(6, 'Tmagna aliquyam erat', NOW(), '2', '2'),"
            "(7, 'Velit esse molestie consequat', NOW(), '4', '3'),"
            "(8, 'Takimata sanctus est', NOW(), '5', '2'),"
            "(9, 'At vero eos et accusam', NOW(), '6', '3');",

            [&res](int num) -> void {
                VLOG(0) << "Query successful";
        },
            [](const std::string& errorString, unsigned int errorNumber) -> void {
                VLOG(0) << "Query failed: " << errorString << " : " << errorNumber;
        });

        webServer.database.mariadb.exec(
            "INSERT INTO `post`(`id`, `text`, `timestamp`, `users__id`, `thread__id`) VALUES "
            "(1, 'quyam erat, sed d', NOW(), '1', '1'),"
            "(2, 'Dolor sit amet. Lorem ipsum dolor', NOW(), '2', '2'),"
            "(3, 'vulputate velit esse molestie consequat ', NOW(), '3', '2'),"
            "(4, 'Psdrz jsdr u', NOW(), '4', '3'),"
            "(5, 'At vero eos et accusam', NOW(), '5', '7'),"
            "(6, 'eros et accumsan', NOW(), '6', '2'),"
            "(7, 'LOL', NOW(), '7', '1'),"
            "(8, 'luptatum zzril delenit', NOW(), '8', '3'),"
            "(9, 'hahahaha', NOW(), '5', '4'),"
            "(10, 'Feugait nulla facilisi!!!!', NOW(), '1', '7'),"
            "(11, 'Duis autem vel eum iriure', NOW(), '6', '5'),"
            "(12, 'PStet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.', NOW(), '4', '1'),"
            "(13, 'LOL', NOW(), '5', '3'),"
            "(14, 'illum dolore eu feugiat nulla?', NOW(), '6', '5'),"
            "(15, 'zzril?!', NOW(), '7', '6'),"
            "(16, 'Lorem ipsum dolor sit amet...', NOW(), '8', '3'),"
            "(17, 'tempor invidunt ut labore', NOW(), '5', '1'),"
            "(18, 'takimata sanctus', NOW(), '1', '9'),"
            "(19, 'Duis autem vel eum iriure dolor in hendrerit in vulputate', NOW(), '6', '5'),"
            "(20, 'Psssssss', NOW(), '2', '6');",

            [&res](int num) -> void {
                VLOG(0) << "Query successful";
        },
            [](const std::string& errorString, unsigned int errorNumber) -> void {
                VLOG(0) << "Query failed: " << errorString << " : " << errorNumber;
        });

        webServer.database.mariadb.exec(
            "INSERT INTO `users`(`id`, `username`, `email`, `password`) VALUES "
            "(1, 'David', 'example@adress.com', 'starman'),"
            "(2, 'Jimi', 'example@adress.com', 'wing67'),"
            "(3, 'Freddy', 'example@adress.com', '12345'),"
            "(4, 'Lou', 'example@adress.com', 'password'),"
            "(5, 'Kate', 'example@adress.com', 'tiktok'),"
            "(6, 'Nina', 'example@adress.com', 'ufosRreal'),"
            "(7, 'Iggy', 'example@adress.com', 'd0g'),"
            "(8, 'Joni', 'example@adress.com', '0000000');",

            [&res](int num) -> void {
                VLOG(0) << "Query successful";
        },
            [](const std::string& errorString, unsigned int errorNumber) -> void {
                VLOG(0) << "Query failed: " << errorString << " : " << errorNumber;
        });

        res.redirect("/");
    });

    // Delete all data from database
    webServer.webApp.get("/deleteAll", [this, &webServer]APPLICATION(req, res){
        webServer.database.mariadb.exec(
            "DELETE FROM `topic`",
            [&res](int num) -> void {
            VLOG(0) << "Delete successful";
        },
            [](const std::string& errorString, unsigned int errorNumber) -> void {
            VLOG(0) << "Query failed: " << errorString << " : " << errorNumber;
        });

        webServer.database.mariadb.exec(
            "DELETE FROM `thread`;",
            [&res](int num) -> void {
            VLOG(0) << "Delete successful";
        },
            [](const std::string& errorString, unsigned int errorNumber) -> void {
            VLOG(0) << "Query failed: " << errorString << " : " << errorNumber;
        });

        webServer.database.mariadb.exec(
            "DELETE FROM `post`;",
            [&res](int num) -> void {
            VLOG(0) << "Delete successful";
        },
            [](const std::string& errorString, unsigned int errorNumber) -> void {
            VLOG(0) << "Query failed: " << errorString << " : " << errorNumber;
        });

        webServer.database.mariadb.exec(
            "DELETE FROM `users`;",
            [&res](int num) -> void {
            VLOG(0) << "Delete successful";
        },
            [](const std::string& errorString, unsigned int errorNumber) -> void {
            VLOG(0) << "Query failed: " << errorString << " : " << errorNumber;
        });
        res.redirect("/");
    });
}

#include <snode.c/express/middleware/StaticMiddleware.h>

#include "WebServer.h"




WebServer::WebServer(int argc, char* argv[])
{
    express::legacy::in::WebApp::init(argc, argv);

    webApp = express::legacy::in::WebApp("legacy");


    initRoutes();
    listen();
}

int WebServer::start()
{
    return express::WebApp::start();
}

void WebServer::initRoutes()
{
    webApp.get("/insert",
               [this]APPLICATION(req, res) {

                   // DB example
                   this->database.mariadb.exec(
                        "INSERT INTO `users`(`username`, `email`, `password`) VALUES ('Chris Volkerino', 'chris@volkerino.at', 'hagenberg')",
                        [](int num) -> void {
                            VLOG(0) << "Query successful: " << num;     // num = affected rows I guess
                        },
                        [](const std::string& errorString, unsigned int errorNumber) -> void {
                            VLOG(0) << "Query failed: " << errorString << " : " << errorNumber;
                        });

                   res.send("Inserted!");
               });

    webApp.get("/select",
               [this]APPLICATION(req, res) {

                   // DB example
                   this->database.mariadb.query(
                        "SELECT * FROM `users`",
                        [](const MYSQL_ROW row) -> void {   // Gets called for each row found.
                            VLOG(0) << "Query successful:";

                            if (row != nullptr) {
                                VLOG(0) << "Result: " << row[0] << " : " << row[1];     // Array index = column index of table.
                            } else {
                                VLOG(0) << "No Result";
                            }
                        },
                        [](const std::string& errorString, unsigned int errorNumber) -> void {
                            VLOG(0) << "Query failed: " << errorString << " : " << errorNumber;
                        });

                   res.send("Selected!");
               });

    webApp.get("/content",
               [this]APPLICATION(req, res) {
                    if(loggedInAs == ""){
                        res.send("Access denied!");
                   } else {
                      res.send("Hidden Content acessed, Logged in as " + loggedInAs);
                   }

               });


    // Base route has to defined last, or it will overrite all other routes.


    registerPage.defineRoutes(webApp, this->database, loggedInAs);
    loginPage.defineRoutes(webApp, this->database, loggedInAs);

    //legacyApp.use(express::middleware::StaticMiddleware("/home/student/dev/snode.c-doc/html"));
}



void WebServer::listen()
{
    webApp.listen([](const express::legacy::in::WebApp::SocketAddress &socketAddress,
                        int err) -> void {
                        if (err != 0) {
                            PLOG(FATAL) << "listen on " << socketAddress.toString();
                        } else {
                            VLOG(0) << "snode.c listening on " << socketAddress.toString();
                        }
    });
}

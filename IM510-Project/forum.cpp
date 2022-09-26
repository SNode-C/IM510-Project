#include "forum.h"

Forum::Forum()
{

}

void Forum::defineRoutes(express::legacy::in::WebApp &WebApp, Database &db, std::string &loggedInAs){

    WebApp.get("/examples", [this, &db, &WebApp, &loggedInAs]APPLICATION(req, res){

        db.mariadb.exec(
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

        db.mariadb.exec(
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

        db.mariadb.exec(
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

        db.mariadb.exec(
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

    WebApp.get("/delete", [this, &db]APPLICATION(req, res){
        db.mariadb.exec(
            "DELETE FROM `topic`",
            [&res](int num) -> void {
            VLOG(0) << "Delete successful";
        },
            [](const std::string& errorString, unsigned int errorNumber) -> void {
            VLOG(0) << "Query failed: " << errorString << " : " << errorNumber;
        });
        db.mariadb.exec(
            "DELETE FROM `thread`;",
            [&res](int num) -> void {
            VLOG(0) << "Delete successful";
        },
            [](const std::string& errorString, unsigned int errorNumber) -> void {
            VLOG(0) << "Query failed: " << errorString << " : " << errorNumber;
        });

        db.mariadb.exec(
            "DELETE FROM `post`;",
            [&res](int num) -> void {
            VLOG(0) << "Delete successful";
        },
            [](const std::string& errorString, unsigned int errorNumber) -> void {
            VLOG(0) << "Query failed: " << errorString << " : " << errorNumber;
        });

        db.mariadb.exec(
            "DELETE FROM `users`;",
            [&res](int num) -> void {
            VLOG(0) << "Delete successful";
        },
            [](const std::string& errorString, unsigned int errorNumber) -> void {
            VLOG(0) << "Query failed: " << errorString << " : " << errorNumber;
        });
        res.redirect("/");
    });


    WebApp.post("/register", [this, &db, &WebApp, &loggedInAs]APPLICATION(req, res) {
        res.redirect("/register");
    });

    WebApp.post("/login", [this, &db, &WebApp, &loggedInAs]APPLICATION(req, res) {
        res.redirect("/login");
    });

    WebApp.get("/posts", [this, &db, &loggedInAs]APPLICATION(req, res){

        std::string url = req.originalUrl;
        std::size_t pos = url.find("?");
        std::string currentThreadId = url.substr(pos +1);

        posts="";

        std::string loggedIn = "Not logged in";
        if (loggedInAs != "") {
            loggedIn = "Logged in as: " + loggedInAs;
        }

        db.mariadb.query(
            "SELECT post.text, post.timestamp, users.username "
            "FROM `post` "
            "INNER JOIN `users` ON post.users__id=users.id "
            "INNER JOIN `thread` ON post.thread__id=thread.id "
            "WHERE post.thread__id=" + currentThreadId,
            [this, &db, &res, currentThreadId, loggedIn](const MYSQL_ROW row) -> void  {

                if (row != nullptr) {

                    posts = posts +
                        "<div class=\"comment\" >"
                        "    <div class=\"comment-info\">"
                        "        <p class=\"user\">"
                                     + std::string(row[2]) +
                        "        </p>"
                        "        <p class=\"comment-timestamp\">"
                                     + std::string(row[1]) +
                        "        </p>"
                        "    </div>"
                        "    <div class=\"comment-content\">"
                                 + std::string(row[0]) +
                        "    </div>"
                        "</div>"
                    ;
                } else {

                    res.send(
                       "<body>"
                       "    <div class=\"banner\">"
                       "        <a href=\"/\">"
                       "           <h1>"
                       "                Forum"
                       "           </h1>"
                       "        </a>"
                       "    </div>"
                       "    <div class=\"buttons\">"
                       "        <a href=\"register\">"
                       "           <button>Register</button>"
                       "       </a>"
                       "        <a href=\"/login\">"
                       "           <button>Login</button>"
                       "       </a>"
                                   + loggedIn +
                       "    </div>"
                       "    <div class=\"main\">"
                       "        <div class=\"header\">"
                       "            <h4 class=\"title\">"
                       "                Thread Title"
                       "            </h4>"
                       "        </div>"
                       "        <textarea></textarea><br>"
                       "        <button>add comment</button>"
                       "        <div class=\"comments\">"
                                    + posts +
                       "        </div>"
                       "    </div>"
                       "    <style>"
                       "        body {"
                       "            margin: 0;"
                       "        }"
                       "        a {"
                       "            text-decoration: none;"
                       "            color: black;"
                       "        }"
                       "        h1 {"
                       "            margin: 0;"
                       "        }"
                       "        ul {"
                       "            list-style-type: none;"
                       "            padding: 0;"
                       "        }"
                       "        h4 {"
                       "            margin: 5px 0;"
                       "        }"
                       "        p {"
                       "            margin: 5px 0;"
                       "        }"
                       "        textarea {"
                       "            width: 80%;"
                       "            height: 80px;"
                       "        }"
                       "        button {"
                       "            margin: 10px 3px;"
                       "        }"
                       "        .banner {"
                       "            background-color: #89c8f8;"
                       "            padding: 40px 40px;"
                       "            margin-bottom: 20px;"
                       "        }"
                       "        .main {"
                       "            background-color:  #d9eaf7 ;"
                       "            margin: 20px 40px; "
                       "            padding: 15px 30px;"
                       "            border: 1px;"
                       "            border-style: solid;"
                       "        }"
                       "        .buttons {"
                       "            margin: 0 40px"
                       "        }"
                       "        .timestamp {"
                       "            padding-right: 10px;"
                       "        }"
                       "        .comments {"
                       "            margin: 40px 0;"
                       "        }"
                       "        .comment {"
                       "            margin: 10px 0;"
                       "        }"
                       "        .row {"
                       "            padding: 5px 0;"
                       "        }"
                       "        .thread-info, .comment-info {"
                       "            display: flex;"
                       "            color: grey;"
                       "            font-size: 12px;"
                       "        }"
                       "        .timestamp {"
                       "            padding-right: 10px;"
                       "        }"
                       "        .comment-timestamp {"
                       "            padding-left: 10px;"
                       "        }"
                       "    </style>"
                       " </body>"

                    );
                    VLOG(0) << "finish";
                }
            },
            [](const std::string& errorString, unsigned int errorNumber) -> void {
                VLOG(0) << "Query failed: " << errorString << " : " << errorNumber;
        });
    });


    WebApp.get("/threads", [this, &db, &loggedInAs]APPLICATION(req, res){

        std::string url = req.originalUrl;
        std::size_t pos = url.find("?");
        std::string currentTopicId = url.substr(pos +1);
        //int currentTopicId = stoi(param);

        threads="";

        std::string loggedIn = "Not logged in";
        if (loggedInAs != "") {
            loggedIn = "Logged in as: " + loggedInAs;
        }

        db.mariadb.query(
            "SELECT thread.id, thread.name, thread.timestamp, users.username "
            "FROM `thread` "
            "INNER JOIN `users` ON thread.users__id=users.id "
            "WHERE thread.topic__id=" + currentTopicId,
            [this, &db, &res, currentTopicId, loggedIn](const MYSQL_ROW row) -> void  {

                if (row != nullptr) {

                    threads = threads +
                        "<li class=\"row\">"
                        "   <a href=\"posts?" + std::string(row[0]) + "\">"
                        "           <h4 class=\"title\" >"
                                        + std::string(row[1]) +
                        "           </h4>"

                        "   <div class=\"thread-info\">"
                        "       <p class=\"timestamp\">"
                                    + std::string(row[2]) + " by " + std::string(row[3]) +
                        "       </p>"
                        "   </div>"
                        "   </a>"
                        "</li><hr>"
                    ;

                } else {

                    res.send(
                        "<body>"
                        "    <div class=\"banner\">"
                        "        <a href=\"/\">"
                        "           <h1>"
                        "                Forum"
                        "           </h1>"
                        "        </a>"
                        "    </div>"
                        "    <div class=\"buttons\">"
                        "        <a href=\"register\">"
                        "           <button>Register</button>"
                        "       </a>"
                        "        <a href=\"/login\">"
                        "           <button>Login</button>"
                        "       </a>"
                        "           <button disabled>Create Thread</button>"
                                    + loggedIn +
                        "    </div>"
                        "    <div class=\"main\">"
                        "        <ul><hr>"
                                    + threads +
                        "        </ul>"
                        "    </div>"
                        "    <style>"
                        "        body {"
                        "            margin: 0;"
                        "        }"
                        "        a {"
                        "            text-decoration: none;"
                        "            color: black;"
                        "        }"
                        "        h1 {"
                        "            margin: 0;"
                        "        }"
                        "        ul {"
                        "            list-style-type: none;"
                        "            padding: 0;"
                        "        }"
                        "        h4 {"
                        "            margin: 5px 0;"
                        "        }"
                        "        p {"
                        "            margin: 5px 0;"
                        "        }"
                        "        textarea {"
                        "            width: 80%;"
                        "            height: 80px;"
                        "        }"
                        "        button {"
                        "            margin: 10px 3px;"
                        "        }"
                        "        .banner {"
                        "            background-color: #89c8f8;"
                        "            padding: 40px 40px;"
                        "            margin-bottom: 20px;"
                        "        }"
                        "        .main {"
                        "            background-color:  #d9eaf7 ;"
                        "            margin: 20px 40px; "
                        "            padding: 15px 30px;"
                        "            border: 1px;"
                        "            border-style: solid;"
                        "        }"
                        "        .buttons {"
                        "            margin: 0 40px"
                        "        }"
                        "        .timestamp {"
                        "            padding-right: 10px;"
                        "        }"
                        "        .comments {"
                        "            margin: 40px 0;"
                        "        }"
                        "        .comment {"
                        "            margin: 10px 0;"
                        "        }"
                        "        .row {"
                        "            padding: 5px 0;"
                        "        }"
                        "        .thread-info, .comment-info {"
                        "            display: flex;"
                        "            color: grey;"
                        "            font-size: 12px;"
                        "        }"
                        "        .timestamp {"
                        "            padding-right: 10px;"
                        "        }"
                        "        .comment-timestamp {"
                        "            padding-left: 10px;"
                        "        }"
                        "    </style>"
                        "</body>"
                    );
                }
            },
            [](const std::string& errorString, unsigned int errorNumber) -> void {
                VLOG(0) << "Query failed: " << errorString << " : " << errorNumber;
        });
    });

    WebApp.get("/", [this, &db, &loggedInAs]APPLICATION(req, res){

        topics="";

        std::string loggedIn = "Not logged in";
        if (loggedInAs != "") {
            loggedIn = "Logged in as: " + loggedInAs;
        }

        db.mariadb.query(
            "SELECT * FROM `topic`",
            [this, &db, &res, loggedIn](const MYSQL_ROW row) -> void  {
                if (row != nullptr) {
                    topics = topics +
                        "<li class=\"row\">"
                        "   <a href=\"threads?" + std::string(row[0]) + "\">"
                        "           <h4 class=\"title\" >"
                                        + std::string(row[1]) +
                        "           </h4>"
                        "   </a>"
                        "</li><hr>"
                        ;
                } else {
                    res.send(
                        "<body>"
                        "    <div class=\"banner\">"
                        "        <h1>"
                        "            Forum"
                        "        </h1>"
                        "    </div>"
                        "    <div class=\"buttons\">"
                        "        <a href=\"register\">"
                        "           <button>Register</button>"
                        "       </a>"
                        "        <a href=\"/login\">"
                        "           <button>Login</button>"
                        "       </a>"
                        "           <button disabled>Create Topic</button>"
                        "        <a href=\"examples\">"
                        "           <button>Insert Examples</button>"
                        "       </a>"
                        "        <a href=\"/delete\">"
                        "           <button>Delete All</button>"
                        "       </a>"
                                    + loggedIn +
                        "    </div>"
                        "    <div class=\"main\">"
                        "        <ul><hr>"
                                    + topics +
                        "        </ul>"
                        "    </div>"
                        "    <style>"
                        "        body {"
                        "            margin: 0;"
                        "        }"
                        "        a {"
                        "            text-decoration: none;"
                        "            color: black;"
                        "        }"
                        "        h1 {"
                        "            margin: 0;"
                        "        }"
                        "        ul {"
                        "            list-style-type: none;"
                        "            padding: 0;"
                        "        }"
                        "        h4 {"
                        "            margin: 5px 0;"
                        "        }"
                        "        p {"
                        "            margin: 5px 0;"
                        "        }"
                        "        textarea {"
                        "            width: 80%;"
                        "            height: 80px;"
                        "        }"
                        "        button {"
                        "            margin: 10px 3px;"
                        "        }"
                        "        .banner {"
                        "            background-color: #89c8f8;"
                        "            padding: 40px 40px;"
                        "            margin-bottom: 20px;"
                        "        }"
                        "        .main {"
                        "            background-color:  #d9eaf7 ;"
                        "            margin: 20px 40px; "
                        "            padding: 15px 30px;"
                        "            border: 1px;"
                        "            border-style: solid;"
                        "        }"
                        "        .buttons {"
                        "            margin: 0 40px"
                        "        }"
                        "        .timestamp {"
                        "            padding-right: 10px;"
                        "        }"
                        "        .comments {"
                        "            margin: 40px 0;"
                        "        }"
                        "        .comment {"
                        "            margin: 10px 0;"
                        "        }"
                        "        .row {"
                        "            padding: 5px 0;"
                        "        }"
                        "        .thread-info, .comment-info {"
                        "            display: flex;"
                        "            color: grey;"
                        "            font-size: 12px;"
                        "        }"
                        "        .timestamp {"
                        "            padding-right: 10px;"
                        "        }"
                        "        .comment-timestamp {"
                        "            padding-left: 10px;"
                        "        }"
                        "    </style>"
                        "</body>"
                    );
                }
            },
            [](const std::string& errorString, unsigned int errorNumber) -> void {
                VLOG(0) << "Query failed: " << errorString << " : " << errorNumber;
        });
    });
}

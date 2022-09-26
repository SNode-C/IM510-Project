#include "registerpage.h"

RegisterPage::RegisterPage()
{

}



//keyword is the thing that will be "cut out"
std::string RegisterPage::parseRequest(std::string &str, const std::string &keyword)
{
    int line = 0;
    int goalLine = 0;
    int nCount = 0;
    bool inRightLine = false;

    std::string newString = "";

    if(keyword == "uname"){
        goalLine = 3;
    } else if(keyword == "email"){
        goalLine = 7;
    } else if(keyword == "password"){
        goalLine = 11;
    }

    for(int i = 0; i < str.size(); i++){
        if(inRightLine){
           if(str[i] == '\r'){
                break;
            }

           newString = newString + str[i];
        }else {
            if(str[i] == '\n'){
                nCount++;
                if(nCount == goalLine){
                    inRightLine = true;
                }
            }
        }
    }



    return newString;
}


//depending on how many line breaks are in the response, we can determine whether or not it is a loginattempt
bool RegisterPage::isRegister(std::string& res){
    int count = 0;
    for(int i = 0; i < res.size(); i++){


        if(res[i] == '\r'){
            count++;
        }
    }

    if(count > 3){
        return true;
    }
    return false;
}


void RegisterPage::defineRoutes(express::legacy::in::WebApp &WebApp, Database &db, std::string &loggedInAs){
    WebApp.get("/register", [this]APPLICATION(req, res){

                   res.send(GetHTML());
               });

    WebApp.post("/register", [this, &db, &WebApp, &loggedInAs]APPLICATION(req, res){
                    std::string body = "";
                    body.assign(req.body.begin(), req.body.end());

                    std::string userName = parseRequest(body, "uname");
                    std::string email = parseRequest(body, "email");
                    std::string password = parseRequest(body, "password");



                    if(!isRegister(body)){
                        res.redirect("/");
                        return;
                    }

                    if(userName.size() == 0 || email.size() == 0 || password.size() == 0){
                        loggedInAs = "";
                        res.redirect("/register");
                        return;
                    }

                    this->success = 1;

                    db.mariadb.query(
                                "SELECT * FROM `users`",
                                [this, userName, email, password, &db, &res, &loggedInAs](const MYSQL_ROW row) -> void {   // Gets called for each row found.
                        if (row != nullptr) {
                            if(row[1] == userName){
                                this->success = 0;
                            }
                            if(row[2] == email){
                                this->success = 0;
                            }
                        } else {
                            if(this->success == 1){
                                db.mariadb.exec(
                                            "INSERT INTO `users`(`username`, `email`, `password`) VALUES ('" + userName + "', '" + email + "', '" + password +"')",
//                                          [&res, &loggedInAs, userName](int num) -> void {
//                                  VLOG(0) << "Query successful: " << num;     // num = affected rows I guess
                                            [&res, &loggedInAs, userName]() -> void {
                                    VLOG(0) << "Query successful";     // num = affected rows I guess
                                    loggedInAs = userName;
                                    res.redirect("/");
                                },
                                [](const std::string& errorString, unsigned int errorNumber) -> void {
                                    VLOG(0) << "Query failed: " << errorString << " : " << errorNumber;
                                });
                            } else {
                                loggedInAs = "";
                                res.redirect("/register");
                            }

                        }

                    },
                    [](const std::string& errorString, unsigned int errorNumber) -> void {
                        VLOG(0) << "Query failed: " << errorString << " : " << errorNumber;
                    });
    });

}

std::string RegisterPage::GetHTML(){
    return "<h1>Register</h1>"
           "<hr>"
           "<form method=\"post\" enctype=\"multipart/form-data\">"
           "<label for='uname'> Username </label> <br>"
           "<input type='text' id='uname' name='uname'><br>"
           "<label for='uname'> Email </label> <br>"
           "<input type='text' id='email' name='email'><br>"
           "<label for='pword'> Password </label> <br>"
           "<input type='password' id='pword' name='pword'><br>"
           "<button id='loginButton'> Register! </button>"
           "</form>"
           "<form method=\"post\" enctype=\"multipart/form-data\">"
           "<button id='registerButton'> Already have an account? Log in here </button>"
           "</form>";
}



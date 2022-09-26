#include "loginpage.h"


LoginPage::LoginPage()
{

}


//keyword is the thing that will be "cut out"
std::string LoginPage::parseRequest(std::string &str, const std::string &keyword)
{
    int line = 0;
    int goalLine = 0;
    int nCount = 0;
    bool inRightLine = false;

    std::string newString = "";

    if(keyword == "uname"){
        goalLine = 3;
    } else if(keyword == "pword"){
        goalLine = 7;
    } else {
        return "Something went wrong";
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
bool LoginPage::isLogin(std::string& res){
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





void LoginPage::defineRoutes(express::legacy::in::WebApp &WebApp, Database &db, std::string &loggedInAs){
    WebApp.get("/login", [this]APPLICATION(req, res){

                   res.send(GetHTML());
               });


    WebApp.post("/login", [this, &db, &WebApp, &loggedInAs]APPLICATION(req, res) {
        found = 0;

        std::string body = "";
        body.assign(req.body.begin(), req.body.end());

        std::string userName = parseRequest(body, "uname");
        std::string password = parseRequest(body, "pword");




        if(isLogin(body)){
            if(userName.size() != 0 && password.size() != 0){



                db.mariadb.query(
                            "SELECT * FROM `users`",
                            [this, userName, password, &res, &loggedInAs](const MYSQL_ROW row) -> void {   // Gets called for each row found.
                    if (row != nullptr) {
                        if(row[1] == userName && row[3] == password){

                            this->found = 1;
                            VLOG(0) << this->found;
                        }
                    } else {
                        if(this->found == 1){
                            loggedInAs = userName;
                        }
                        res.redirect("/");
                    }
                },
                [](const std::string& errorString, unsigned int errorNumber) -> void {
                    VLOG(0) << "Query failed: " << errorString << " : " << errorNumber;
                });
            } else {
                loggedInAs = "";
                res.redirect("/");
            }
        } else {
            res.redirect("/register");
        }
    });
}



std::string LoginPage::GetHTML(){
    return "<h1>Login</h1>"
           "<hr>"
           "<form method=\"post\" enctype=\"multipart/form-data\">"
               "<label for='uname'> Username </label> <br>"
               "<input type='text' id='uname' name='uname'><br>"
               "<label for='pword'> Password </label> <br>"
               "<input type='password' id='pword' name='pword'><br>"
               "<button id='loginButton'> Login! </button>"
           "</form>"
           "<form method=\"post\" enctype=\"multipart/form-data\">"
               "<button id='registerButton'> Register Here! </button>"
           "</form>";
}

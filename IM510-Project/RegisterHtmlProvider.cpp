#include "RegisterHtmlProvider.h"

#include "StyleHtmlProvider.h"

RegisterHtmlProvider::RegisterHtmlProvider()
{

}

// Gets html content of register page
std::string RegisterHtmlProvider::getHtml()
{
    StyleHtmlProvider styleProvider;

    return  "<div class=\"banner\">"
                "<h1>"
                    "<a href=\"/\">Forum</a> / Register"
                "</h1>"
            "</div>"
            "<div class=\"main\">"
                "<div class=\"header\">"
                    "<h4 class=\"title\">Don't have an account? Register!</h4>"
                "</div>"
                "<form method=\"post\" enctype=\"multipart/form-data\">"
                    "<label for='uname'> Username </label> <br>"
                    "<input type='text' id='uname' name='uname'><br>"
                    "<label for='uname'> Email </label> <br>"
                    "<input type='text' id='email' name='email'><br>"
                    "<label for='pword'> Password </label> <br>"
                    "<input type='password' id='pword' name='pword'><br>"
                    "<button id='loginButton'>Register!</button>"
               "</form>"
           "<hr/>"
           "<div class=\"header\">"
               "<h4 class=\"title\">Already have an account? Login!</h4>"
           "</div>"
           "<a href=\"/login\">"
                "<button id='registerButton'>Login</button>"
           "</a>"
           "</div>"
           + styleProvider.getHtml();
}

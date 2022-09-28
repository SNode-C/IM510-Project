#include "LoginHtmlProvider.h"

#include "StyleHtmlProvider.h"

LoginHtmlProvider::LoginHtmlProvider()
{

}

// Gets html content of login page
std::string LoginHtmlProvider::getHtml()
{
    StyleHtmlProvider styleProvider;

    return  "<div class=\"banner\">"
                "<h1>"
                    "<a href=\"/\">Forum</a> / Login"
                "</h1>"
            "</div>"
            "<div class=\"main\">"
                "<div class=\"header\">"
                    "<h4 class=\"title\">Already have an account? Login!</h4>"
                "</div>"
                "<form method=\"post\" enctype=\"multipart/form-data\">"
                    "<label for='uname'> Username </label> <br>"
                    "<input type='text' id='uname' name='uname'><br>"
                    "<label for='password'> Password </label> <br>"
                    "<input type='text' id='password' name='password'><br>"
                    "<button id='loginButton'>Login</button>"
                "</form>"
            "<hr/>"
            "<div class=\"header\">"
                "<h4 class=\"title\">Don't have an account? Register!</h4>"
            "</div>"
            "<a href=\"/register\">"
                "<button id='registerButton'>Register</button>"
            "</a>"
            "</div>"
            + styleProvider.getHtml();
}


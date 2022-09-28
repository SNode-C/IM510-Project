#ifndef LOGINHTMLPROVIDER_H
#define LOGINHTMLPROVIDER_H

#include "AbstractHtmlProvider.h"

class LoginHtmlProvider : AbstractHtmlProvider
{
public:
    LoginHtmlProvider();
    virtual std::string getHtml() override;
};

#endif // LOGINHTMLPROVIDER_H

#ifndef REGISTERHTMLPROVIDER_H
#define REGISTERHTMLPROVIDER_H

#include "AbstractHtmlProvider.h"

class RegisterHtmlProvider : AbstractHtmlProvider
{
public:
    RegisterHtmlProvider();
    virtual std::string getHtml() override;
};

#endif // REGISTERHTMLPROVIDER_H

#ifndef ABSTRACTHTMLPROVIDER_H
#define ABSTRACTHTMLPROVIDER_H

#include <string>

class AbstractHtmlProvider
{
public:
    AbstractHtmlProvider();
    virtual std::string getHtml() = 0;
};

#endif // ABSTRACTHTMLPROVIDER_H

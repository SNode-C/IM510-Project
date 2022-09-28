#ifndef STYLEHTMLPROVIDER_H
#define STYLEHTMLPROVIDER_H

#include "AbstractHtmlProvider.h"

class StyleHtmlProvider : AbstractHtmlProvider
{
public:
    StyleHtmlProvider();
    virtual std::string getHtml() override;
};

#endif // STYLEHTMLPROVIDER_H

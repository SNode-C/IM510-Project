#include <iostream>

#include "WebServer.h"

using namespace std;

int main(int argc, char* argv[])
{
    WebServer webServer(argc, argv);

    return webServer.start();
}

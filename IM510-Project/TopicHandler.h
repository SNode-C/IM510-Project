#ifndef TOPICHANDLER_H
#include <string>
#include <snode.c/express/legacy/in/WebApp.h>
#include "Database.h"
#define TOPICHANDLER_H

class TopicHandler
{
private:
    express::legacy::in::WebApp webApp;
    Database db;

public:
    TopicHandler();

    void init(express::legacy::in::WebApp &WebApp, Database &db);
    void createNewTopic(std::string& topicName, unsigned int userId);
    void createNewThread(std::string& threadName, int userId, int topicId);
    void createNewPost(std::string& text, int threadId, int userId);
    std::string currentDateTime();
};

#endif // TOPICHANDLER_H

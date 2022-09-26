#include "TopicHandler.h"

TopicHandler::TopicHandler() {

}

void TopicHandler::init(express::legacy::in::WebApp &WebApp, Database &db) {
    this->db = db;
    this->webApp = WebApp;
}

void TopicHandler::createNewTopic(std::string &topicName, unsigned int userId) {
    std::string parseTimeStamp = currentDateTime();
    std::string parseUserId = std::to_string(userId);
    std::string topicId;

    db.mariadb.exec(
            "INSERT INTO `topic`(`name`, `timestamp`, `users__id`) VALUES('" + topicName + "', '" +
            parseTimeStamp + "', '" + parseUserId + "')", [](int num) -> void {
                VLOG(0) << "Topic added successfully.";
            },
            [](const std::string &error, unsigned int errorNum) -> void {
                VLOG(0) << "Adding new topic failed: " << error << ", " << errorNum << ".";
            });
}

void TopicHandler::createNewThread(std::string &threadName, int userId, int topicId) {
    std::string parseTimeStamp = currentDateTime();
    std::string parseUserId = std::to_string(userId);
    std::string parseTopicId = std::to_string(topicId);

    db.mariadb.exec(
            "INSERT INTO `thread`(`name`, `timestamp`, `users__id`,`topic__id`) VALUES('" + threadName + "', '" +
            parseTimeStamp + "', '" + parseUserId + "', '" + parseTopicId +"')", [](int num) -> void {
                VLOG(0) << "Thread added successfully.";
            },
            [](const std::string &error, unsigned int errorNum) -> void {
                VLOG(0) << "Adding new thread failed: " << error << ", " << errorNum << ".";
            });
}

void TopicHandler::createNewPost(std::string &text, int threadId, int userId) {
    std::string parseTimeStamp = currentDateTime();
    std::string parseUserId = std::to_string(userId);
    std::string parseThreadId = std::to_string(threadId);

    db.mariadb.exec(
            "INSERT INTO `thread`(`text`, `timestamp`, `users__id`,`thread__id`) VALUES('" + text + "', '" +
            parseTimeStamp + "', '" + parseUserId + "', '" + parseThreadId +"')", [](int num) -> void {
                VLOG(0) << "Post added successfully.";
            },
            [](const std::string &error, unsigned int errorNum) -> void {
                VLOG(0) << "Adding new post failed: " << error << ", " << errorNum << ".";
            });
}

std::string TopicHandler::currentDateTime() {
    time_t now = time(0);
    struct tm tstruct{};
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return buf;
}
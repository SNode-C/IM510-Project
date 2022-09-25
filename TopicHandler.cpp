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
    db.mariadb.exec(
            "INSERT INTO `topic`(`name`, `timestamp`, `users__id`) VALUES('" + topicName + "', '" +
            parseTimeStamp + "', '" + parseUserId + "')", [](int num) -> void {
                VLOG(0) << "Topic added successfully.";
            },
            [](const std::string &error, unsigned int errorNum) -> void {
                VLOG(0) << "Adding new topic failed: " << error << ", " << errorNum << ".";
            });
}

void TopicHandler::deleteTopic(int topicId) {

}

void TopicHandler::queryTopic(int topicId) {
    std::string parseTopicId = std::to_string(topicId);
    db.mariadb.query(
            "SELECT * FROM `topic`", [parseTopicId]
                    (const MYSQL_ROW row) -> void {
                if (row != nullptr && row[0] == parseTopicId) {
                    VLOG(0) << "Found topic:" << row[1] << ", " << row[2] << ", " << row[3];
                }
            },
            [parseTopicId](const std::string &errorStr, unsigned int errorNum) -> void {
                VLOG(0) << "Query Failed. No topic with id " + parseTopicId + " found.";
            });
}

void TopicHandler::queryTopic(const std::string &topicName) {
    std::string timeStamp;
    std::string userId;
    db.mariadb.query(
            "SELECT * FROM `topic` WHERE `name`='" + topicName + "'", [topicName, timeStamp, userId]
                    (const MYSQL_ROW row) -> void {
                if (row != nullptr) {
                    VLOG(0) << topicName;
                }
            },
            [topicName](const std::string &errorStr, unsigned int errorNum) -> void {
                VLOG(0) << "Query Failed. No topic by name " + topicName + " found";
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

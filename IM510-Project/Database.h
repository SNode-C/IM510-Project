#ifndef DATABASE_H
#define DATABASE_H

#include <snode.c/database/mariadb/MariaDBClient.h>

class Database
{
public:
    database::mariadb::MariaDBConnectionDetails mariadbDetails = {
        .hostname = "localhost",
        .username = "IM510",
        .password = "IM510",
        .database = "IM510_Project",
        .port = 3306,
        .socket = "/run/mysqld/mysqld.sock",
        .flags = 0,
    };

    database::mariadb::MariaDBClient mariadb;

    Database();
};

#endif // DATABASE_H

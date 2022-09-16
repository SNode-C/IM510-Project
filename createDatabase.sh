#!/bin/sh

# Drop and create database.
sudo mysql -e "DROP DATABASE IM510_Project;"
sudo mysql -e "CREATE DATABASE IM510_Project;"

# Create tables.
sudo mysql -e "CREATE TABLE IM510_Project.test (username text NOT NULL, password text NOT NULL) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;"

# Drop and create user.
sudo mysql -e "DROP USER IM510@localhost;"
sudo mysql -e "CREATE USER IM510@localhost IDENTIFIED BY 'IM510';"
sudo mysql -e "GRANT ALL PRIVILEGES ON *.* TO IM510@localhost;"
sudo mysql -e "GRANT ALL PRIVILEGES ON IM510_Project.test TO IM510@localhost;"

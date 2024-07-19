#ifndef CSQL_H
#define CSQL_H

#pragma once

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>
#include <iostream>

using namespace std;

class CSQL
{
public:
    CSQL(const string& host, const string& user, const string& password, const string& database);
    ~CSQL();
    void innsertPerson(const string& name, int age);
    void selectPerson();

private:
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* pstmt;
};

#endif
#ifndef CHEF_H_INCLUDED
#define CHEF_H_INCLUDED
#include "main.h"
#include "Person.h"

class Chef : public PersonTemplate
{
    public:
        bool loggedIn = false;
        std::unordered_set<int> orderNums;
        int verifyUser(std::string username1, std::string password1, MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res);
        int login(MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res);
        int viewAndUpdateOrders(MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res);
        int verifyChoice(int choice);
};

#endif // CHEF_H_INCLUDED

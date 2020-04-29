#ifndef ADMIN_H_INCLUDED
#define ADMIN_H_INCLUDED
#include "main.h"
#include "Person.h"

class Admin : public PersonTemplate
{
    public:
        std::unordered_map<int,float> menu_rows;
        bool loggedIn = false;
        int verifyUser(std::string username1, std::string password1, MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res);
        int login(MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res);
        int verifyInput(std::string item_name,std::string item_price);
        int verifyExists(int item_num);
        int addOrRemoveItems(MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res);
        int viewPayments(MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res);
};

#endif // ADMIN_H_INCLUDED

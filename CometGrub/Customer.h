#ifndef CUSTOMER_H_INCLUDED
#define CUSTOMER_H_INCLUDED
#include "main.h"
#include "Person.h"

class Customer : public PersonTemplate
{
    public:
        bool loggedIn = false;
        std::unordered_map<int,float> menu_rows;
        std::vector<int> order;
        int verifyUser(std::string username1, std::string password1, MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res);
        int login(MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res);
        int viewMenu(MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res);
        int placeOrder(MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res);
        int makePayment(MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res);
        int logout();
        int checkValidOrder();
};

#endif // CUSTOMER_H_INCLUDED

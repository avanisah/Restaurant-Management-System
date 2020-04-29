#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include "main.h"

using namespace std;

//Template pattern class

class PersonTemplate
{
    protected:
        std::string username;
        std::string name;
        std::string address;
        int login(MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res);
        int logout();
};

#endif // PERSON_H_INCLUDED

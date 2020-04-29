#ifndef USERLOGIN_H_INCLUDED
#define USERLOGIN_H_INCLUDED
#include "main.h"


//Singleton pattern class
class UserLogin
{
    private:
        static UserLogin *user; //Singleton instance of class
        UserLogin(){}
    public:
        static UserLogin *getInstance(){
            if(!user)
                user = new UserLogin;   //Returns the single instance
            return user;
        }
        int userLogin(MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res);
        int verify(int choice, MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res);
        int Register(MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res);
        int verifySignup(std::string name,std::string username,std::string password, std::string password_re, std::string address, MYSQL* conn);
};


#endif // USERLOGIN_H_INCLUDED

//Contains definitions for all the UserLogin class member functions

#include "UserLogin.h"  //Contains the UserLogin class definition

using namespace std;

UserLogin::userLogin(MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res)    //User type selection and registration menu
{
    int choice, ret = 0;
    while(ret==0){
    cout<<"\nEnter the user type: \n1. Customer\n2. Chef\n3. Admin\n4. Register new customer\n5. Exit CometGrub\n\nUser type: ";
    cin>>choice;
    if(choice==5)
        return choice;
    ret = verify(choice, conn, row, res);
    if(ret<1)
        ret = 0;
    }
    return ret;
}

UserLogin::verify(int choice, MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res)   //verification of menu choice
{
    switch(choice)
    {
        case 1:
            cout<<"\nCUSTOMER LOGIN\n";
            return 1;
        case 2:
            cout<<"\nCHEF LOGIN\n";
            return 2;
        case 3:
            cout<<"\nADMIN LOGIN\n";
            return 3;
        case 4:
            if(Register(conn, row, res)==0) {
                cout<<"\nSign up successful. You can now login as a customer.\n";
                system("pause");
                system("cls");
                return 0;
            }
            else {
                cout<<"\nSign up failed. Please try again\n";
                system("pause");
                system("cls");
                return -1;
            }
        default:
            cout<<"\nInvalid input. Please enter one of the above choices only.\n";
            system("pause");
            system("cls");
            return -2;
    }
}

UserLogin::Register(MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res)   //Registration for a new customer
{
    string name,username,password,password_re,address;
    cout<<"\nSIGN UP\n\nEnter your name:";
    cin>>name;
    cout<<"\nEnter a username:";
    cin>>username;
    cout<<"\nEnter a password (Max 13 characters):";
    cin>>password;
    cout<<"\nConfirm password:";
    cin>>password_re;
    cout<<"\nEnter your address:";
    cin>>address;
    if(verifySignup(name,username,password,password_re,address,conn)!=0)
    {
        return 1;
    }

    return 0;
}

UserLogin::verifySignup(string name, string username, string password, string password_re, string address, MYSQL* conn) //Verification of the sign up form
{
    if(password.length()>13)
    {
        cout<<"\nPassword too long";
        return 1;
    }
    if(password!=password_re){
        cout<<"\nPasswords do not match";
        return 2;
    }
    int qstate = 0;
    stringstream ss;
    ss<<"INSERT INTO users(Username, Name, Password, UserType, Address) VALUES ('"<<username<<"','"<<name<<"','"<<password<<"','customer','"<<address<<"');";
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if(qstate!=0)
    {
        cout<<"\nCould not insert into Database. The username already exists.\n";
        return 3;
    }
    return 0;
}

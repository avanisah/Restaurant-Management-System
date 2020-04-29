//COMETGRUB Version 1.0 (Iteration 3 revised)
//Main controller file. Controls the overall flow of the application.
//Application last Modified: 11/25/2019, 8:22 PM CDT

#include "main.h"   //includes all the necessary headers
#include "Tests.h"  //Contains the testing class

using namespace std;

UserLogin* UserLogin::user = 0;
MYSQL* conn;
MYSQL_RES* res;
MYSQL_ROW row;

void mainActivity(Customer& cust)   //Customer activity
{
    while(cust.loggedIn)
    {
        cust.viewMenu(conn,row,res);
        cust.placeOrder(conn,row,res);
        cust.logout();
    }
}

void mainActivity(Chef& chef)   //Chef activity
{
    while(chef.loggedIn)
    {
        chef.viewAndUpdateOrders(conn,row,res);
    }
}

void mainActivity(Admin& admin) //Admin activity
{
    while(admin.loggedIn)
    {
        admin.addOrRemoveItems(conn,row,res);
    }
}

int loginScreen(int type)   //Login screen based on user-type
{
    int resp;
    Customer cust;
    Admin admin;
    Chef chef;
    switch(type)
    {
        case 1:
            resp = cust.login(conn,row,res);
            if(resp==-1)
                return -1;
            else
                system("pause");
                system("cls");
                mainActivity(cust);
            break;
        case 2:
            resp = chef.login(conn,row,res);
            if(resp==-1)
                return -1;
            else
                system("pause");
                system("cls");
                mainActivity(chef);
            break;
        case 3:
            resp = admin.login(conn,row,res);
            if(resp==-1)
                return -1;
            else
                system("pause");
                system("cls");
                mainActivity(admin);
            break;
    }
    cout<<"\nThank you! You have been logged out successfully!\n";
    system("pause");
    system("cls");
    return 0;
}

void loginView()    //The main menu of the application where users can login or signup
{
    int resp,resp2=0;
    UserLogin *user1 = user1->getInstance();    //Accessing the singleton object
    while(resp2==0){
        resp = user1->userLogin(conn,row,res);
        if(resp==5)
            return;
        resp2 = loginScreen(resp);
    }
}

int main()  //Main function
{
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "127.0.0.1", "root", "", "cometgrub", 0, NULL, 0);  //Setting up the DB connectivity
    if(conn)
    {
        /*//Uncomment this code to run test cases.
        Tests test;
        test.runAllTests(conn);
        cout<<"\nTesting complete.\n";
        system("pause");
        system("cls");*/
        system("color 2F");
        cout << "CometGrub - version 0.3 (iteration 3)" << endl;
        loginView();
        cout<<"\n\nThank you for using CometGrub!\n";
        system("pause");
    }
    else
    {
        cout<<"Database connection failure";
    }
    return 0;
}

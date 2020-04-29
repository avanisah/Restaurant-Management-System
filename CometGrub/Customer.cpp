//Contains the implementation for the member functions of the Customer class

#include "Customer.h"   //Includes the Customer class definition

using namespace std;

Customer::login(MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res) //Login for the Customer user
{
    string username1,password1;
    cout<<"\nEnter your username:";
    cin>>username1;
    cout<<"\nEnter your password:";
    cin>>password1;
    int resp = verifyUser(username1,password1,conn,row,res);
    switch(resp)
    {
    case -1:
        cout<<"\nInvalid Username.\n";
        return -1;
    case -2:
        cout<<"\nInvalid password.\n";
        return -1;
    case 0:
        cout<<"\nLogin Successful!\n";
        return 0;
    }
}

Customer::verifyUser(string username1, string password1, MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res)    //Verification of the Customer's credentials
{
    stringstream s1;
    s1<<"SELECT * from users WHERE Username='"<<username1<<"' and UserType='customer';";
    string query = s1.str();
    const char* q = query.c_str();
    int qstate = mysql_query(conn,q);
    if(qstate)
    {
        return -1;
    }
    else
    {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
        if(row[2]==password1)
        {
            username = username1;
            name = row[1];
            address = row[4];
            loggedIn = true;
            return 0;
        }
        else
        {
            return -2;
        }
    }
}

Customer::viewMenu(MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res)  //Displays the restaurant menu to the Customer
{
    cout<<"Welcome Customer!\n\nMENU\nItem ID\t\tItem Name\t\t\tPrice"<<endl;
    int qstate = mysql_query(conn, "SELECT * from menu;");
    if(!qstate)
        res = mysql_store_result(conn);
    else
        return -1;
    row = mysql_fetch_row(res);
    int index;
    float val;
    while(row)
    {
        cout<< row[0]<<"\t\t"<<row[1]<<"\t\t\t$"<<row[2]<<endl<<endl;
        index = stoi(row[0]);
        val = stof(row[2]);
        menu_rows[index] = val;
        row = mysql_fetch_row(res);
    }
    return 0;
}

Customer::placeOrder(MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res)    //Allows the customer to place an order
{
    int x;
    stringstream ss;
    string query;
    const char* q;
    ordering:
    cout<<"\nEnter the items that you wish to purchase\nYou can enter the same number multiple times. Type '-1' to finish the order (Or type -2 to logout):";
    order.clear();
    while(1)
    {
        cin>>x;
        if(x==-2)
        {
            logout();
            goto exit;
        }
        if(x==-1)
            break;
        order.push_back(x);
    }
    switch(checkValidOrder())
    {
        case 0:
            if(makePayment(conn,row,res)==1) {
                cout<<"\nOrder placed successfully\n";
                ss<<"INSERT INTO orders(Username, ItemList) VALUES ('"<<username<<"','";
                for(int i=0;i<order.size();i++)
                {
                    ss<<order[i]<<",";
                }
                ss<<"');";
                query = ss.str();
                q = query.c_str();
                mysql_query(conn,q);
            }
            else
            {
                cout<<"\nAttempt limit exceeded. Order canceled.\n";
                logout();
            }
            break;
        case 1:
            cout<<"\nInvalid order placed. Enter items again.\n";
            goto ordering;
            break;
        case 2:
            cout<<"\nYou didn't order anything. Enter items again.\n";
            goto ordering;
    }
    exit:
        return 0;
}

Customer::makePayment(MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res)       //Handles the customer's order payment
{
    stringstream ss;
    string query;
    const char* q;
    int attempts = 3;
    int choice;
    PaymentStrategy pay;
    float total;
    for(int i=0;i<order.size();i++)
    {
        total+=menu_rows[order[i]];
    }
    while(attempts>0)
    {
        cout<<"Amount to pay : $"<<total;
        cout<<"\nEnter your preferred payment method:\n1.Cash\n2.Card\nchoice:";
        cin>>choice;
        switch(choice)
        {
        case 1:
            if(pay.paymentStrategy(choice)==1) {
            ss<<"INSERT INTO payments(Customer,Amount,Method) VALUES ('"<<username<<"','"<<total<<"','cash');";
            query = ss.str();
            q = query.c_str();
            mysql_query(conn,q);
            return 1;
            }
            else
            {
                --attempts;
                if(attempts==0)
                    break;
                cout<<"\nPayment failed. Try again.\n"<<endl;
            }
        case 2:
            if(pay.paymentStrategy(choice)==1) {
                ss<<"INSERT INTO payments(Customer,Amount,Method) VALUES ('"<<username<<"','"<<total<<"','card');";
                query = ss.str();
                q = query.c_str();
                mysql_query(conn,q);
                return 1;
            }
            else
            {
                --attempts;
                if(attempts==0)
                    break;
                cout<<"\nPayment failed. Try again.\n"<<endl;
            }
        }
    }
    return 0;
}

Customer::logout()  //Customer logout
{
    loggedIn = false;
}

Customer::checkValidOrder() //Checking whether the customer's order is valid
{
    if(order.size()==0)
        return 2;
    for(int i=0;i<order.size();i++)
    {
        if(menu_rows.find(order[i])==menu_rows.end())
            return 1;
    }
    return 0;
}

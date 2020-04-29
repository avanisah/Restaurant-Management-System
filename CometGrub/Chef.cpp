//Contains the implementation for the member functions of the Chef class

#include "Chef.h" //Includes the Chef class definition

using namespace std;

Chef::login(MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res) //Login form for the Chef user
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

Chef::verifyUser(string username1, string password1, MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res)    //Verification of the chef's login credentials
{
    stringstream s1;
    s1<<"SELECT * from users WHERE Username='"<<username1<<"' and UserType='chef';";
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

Chef::viewAndUpdateOrders(MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res)   //Chef's control over the list of pending orders
{
    cout<<"Welcome Chef!\n\nACTIVE ORDERS\nOrder number\t\tCustomer ID\t\t\tItem List\t\t\tStatus"<<endl;
    int choice;
    stringstream ss;
    string query;
    string item_num;
    int qstate = mysql_query(conn, "SELECT * from orders where Status='Pending';");
    if(!qstate)
        res = mysql_store_result(conn);
    else
        return -1;
    row = mysql_fetch_row(res);
    orderNums.clear();
    while(row)
    {
        cout<<row[0]<<"\t\t\t"<<row[1]<<"\t\t\t\t"<<row[2]<<"\t\t\t"<<row[3]<<endl<<endl;
        orderNums.insert(stoi(row[0]));
        row = mysql_fetch_row(res);
    }
    cout<<"\nWhat would you like to do?\n1.Mark order as completed\n2.Logout\n\nchoice:";
    cin>>choice;
    switch(choice)
    {
    case 1:
        cout<<"Enter the order number:";
        cin>>item_num;
        if(verifyChoice(stoi(item_num)))
        {
            ss<<"UPDATE orders SET Status='Completed' WHERE OrderNumber='"<<item_num<<"';";
            query = ss.str();
            const char* qd = query.c_str();
            if(!mysql_query(conn,qd))
                cout<<"\nOrder completed.\n";
        }
        else
        {
           cout<<"\nInvalid entry. Please try again.\n";
        }
        break;
    case 2:
        loggedIn = false;
        break;
    default:
        loggedIn = false;
        break;
    }
}

Chef::verifyChoice(int choice)  //To verify whether the chef's choice exists in the list of orders
{
    if(orderNums.find(choice)==orderNums.end())
        return 0;
    else
        return 1;
}

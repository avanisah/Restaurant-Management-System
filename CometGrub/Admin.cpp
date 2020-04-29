//Contains the implementation for the member functions in the Admin class

#include "Admin.h" //Includes the Admin class definition

using namespace std;

Admin::login(MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res)    //Login form for the Admin user
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

Admin::verifyUser(string username1, string password1, MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res)   //Verification of Admin credentials
{
    stringstream s1;
    s1<<"SELECT * from users WHERE Username='"<<username1<<"' and UserType='admin';";
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

Admin::addOrRemoveItems(MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res) //Admin control over the menu items
{
    cout<<"Welcome Admin!\n\nMENU\nItem ID\t\tItem Name\t\t\tPrice"<<endl;
    int choice;
    string item_name,item_price;
    stringstream ss;
    string query;
    int item_num;
    int qstate = mysql_query(conn, "SELECT * from menu;");
    if(!qstate)
        res = mysql_store_result(conn);
    else
        return -1;
    row = mysql_fetch_row(res);
    int index;
    float val;
    menu_rows.clear();
    while(row)
    {
        cout<<row[0]<<"\t\t"<<row[1]<<"\t\t\t$"<<row[2]<<endl<<endl;
        index = stoi(row[0]);
        val = stof(row[2]);
        menu_rows[index] = val;
        row = mysql_fetch_row(res);
    }
    cout<<"\nWhat would you like to do?\n1.Add item to menu\n2.Remove item from menu\n3.View Payment History\n4.Logout\n\nchoice:";
    cin>>choice;
    switch(choice)
    {
    case 1:
        cout<<"\nEnter the name of the new item (no spaces. Use '_'):";
        cin>>item_name;
        cout<<"\nEnter the price of the new item (2 decimal places):";
        cin>>item_price;
        if(verifyInput(item_name,item_price)==0)
        {
            ss<<"INSERT INTO menu (ItemName, Price) VALUES ('"<<item_name<<"','"<<item_price<<"');";
            query = ss.str();
            const char* qi = query.c_str();
            mysql_query(conn,qi);
            cout<<"\nMenu item added.\n";
        }
        else
        {
            cout<<"\nInvalid entry. Please try again.\n";
        }
        break;
    case 2:
        cout<<"Enter the item number:";
        cin>>item_num;
        if(verifyExists(item_num))
        {
            ss<<"DELETE FROM menu WHERE ItemId='"<<item_num<<"';";
            query = ss.str();
            const char* qd = query.c_str();
            mysql_query(conn,qd);
            cout<<"\nMenu item removed.\n";
        }
        else
        {
           cout<<"\nInvalid entry. Please try again.\n";
        }
        break;
    case 3:
        viewPayments(conn,row,res);
        break;
    case 4:
        loggedIn = false;
        break;
    default:
        loggedIn = false;
        break;
    }
}

Admin::viewPayments(MYSQL* conn, MYSQL_ROW row, MYSQL_RES* res) //Displays the restaurant's payment history
{
    system("cls");
    cout<<"PAYMENT HISTORY\n\nPaymentID\t\tCustomer\t\tAmount\t\tMethod\n";
    int qstate = mysql_query(conn, "SELECT * from payments;");
    if(!qstate)
        res = mysql_store_result(conn);
    else
        return -1;
    row = mysql_fetch_row(res);
    while(row)
    {
        cout<<row[0]<<"\t\t\t"<<row[1]<<"\t\t\t$"<<row[2]<<"\t\t"<<row[3]<<endl<<endl;
        row = mysql_fetch_row(res);
    }
    cout<<endl;
    system("pause");
    system("cls");
    return 1;
}

Admin::verifyExists(int item_num)   //To check if the Admin's choice exists in the menu
{
    if(menu_rows.find(item_num)==menu_rows.end())
        return 0;
    else
        return 1;
}

Admin::verifyInput(string item_name, string item_price) //To check if the admin's entry is valid
{
    if(item_name.length()>15)
        return 1;
    if(!stof(item_price))
        return 2;
    return 0;
}


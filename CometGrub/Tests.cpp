//File containing all the test cases descriptions

#include "Tests.h"

using namespace std;

void Tests::runAllTests(MYSQL* conn)   //Run all the test cases
{
    cout<<"Running all test cases:\n";
    LoginTests(conn);
    AdminTests();
    ChefTests();
    CustomerTests();
}

void Tests::AdminTests()    //Run test cases on the Admin class
{
    cout<<"\nRunning admin test cases:\n";
    testInvalidChoiceAdmin();
    testValidChoiceAdmin();
    testInvalidNameAdmin();
    testValidNameAdmin();
}

void Tests::ChefTests()     //Run test cases on the Chef class
{
    cout<<"\nRunning chef test cases:\n";
    testInvalidChoiceChef();
    testValidChoiceChef();
}

void Tests::CustomerTests() //Run test cases on the Customer class
{
    cout<<"\nRunning customer test cases:\n";
    testInvalidOrder();
    testEmptyOrder();
    testValidOrder();
    testBadCardNumber();
    testCVVError();
    testExpiryDateError();
    testValidCardDetails();
}

void Tests::LoginTests(MYSQL* conn)     //Run test cases on the UserLogin class
{
    cout<<"\nRunning login test cases:\n";
    testPasswordMismatch(conn);
    testPasswordLength(conn);
    testInvalidChoice();
    testValidChoice();
}

void Tests::testPasswordMismatch(MYSQL* conn) //Tests a password mismatch
{
    int ret;
    ret = user->verifySignup("Hello","world","Hello","World","hello world",conn);
    if(ret == 2)
        cout<<"\nPassword Mismatch test case passed\n";
    else
        cout<<"\nPassword Mismatch test case failed\n";
}

void Tests::testPasswordLength(MYSQL* conn) //Tests for length of a password
{
    int ret;
    ret = user->verifySignup("Hello","world","HelloWorldHelloWorldHelloWorldHelloWorld","HelloWorldHelloWorldHelloWorldHelloWorld","hello world",conn);
    if(ret == 1)
        cout<<"\nPassword Length test case passed\n";
    else
        cout<<"\nPassword Length test case failed\n";
}

void Tests::testInvalidChoice() //Tests for an invalid menu choice
{
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    int ret;
    ret = user->verify(100,conn,row,res);
    if(ret==-2)
        cout<<"\nInvalid choice test case passed\n";
    else
        cout<<"\nInvalid choice test case failed\n";
}

void Tests::testValidChoice()   //Tests a valid menu choice
{
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    int ret;
    ret = user->verify(1,conn,row,res);
    if(ret==1)
        cout<<"\nValid choice test case passed\n";
    else
        cout<<"\nValid choice test case failed\n";
}

void Tests::testEmptyOrder()  //Tests for an empty order
{
    int ret;
    cust.order.clear();
    ret = cust.checkValidOrder();
    if(ret==2)
        cout<<"\nEmpty order test case passed\n";
    else
        cout<<"\nEmpty order test case failed\n";
}

void Tests::testInvalidOrder()  //Tests for an order containing invalid items
{
    int ret;
    cust.menu_rows[1] = 0.99;
    cust.order.push_back(50000);
    ret = cust.checkValidOrder();
    if(ret==1)
        cout<<"\nEmpty order test case passed\n";
    else
        cout<<"\nEmpty order test case failed\n";
}

void Tests::testValidOrder()    //Tests for a valid order
{
    int ret;
    cust.menu_rows[1] = 0.99;
    cust.order.push_back(1);
    ret = cust.checkValidOrder();
    if(ret==0)
        cout<<"\nValid order test case passed\n";
    else
        cout<<"\nValid order test case failed\n";
}

void Tests::testInvalidChoiceChef() //Tests for an invalid choice by chef
{
    chef.orderNums.insert(1);
    int ret = chef.verifyChoice(2);
    if(ret==0)
        cout<<"\nInvalid chef choice test case passed\n";
    else
        cout<<"\nInvalid chef choice test case failed\n";
}

void Tests::testValidChoiceChef() //Tests for a Valid choice by chef
{
    chef.orderNums.insert(1);
    int ret = chef.verifyChoice(1);
    if(ret==1)
        cout<<"\nValid chef choice test case passed\n";
    else
        cout<<"\nValid chef choice test case failed\n";
}

void Tests::testInvalidChoiceAdmin()    //Tests for an invalid choice by admin
{
    admin.menu_rows[1] = 0.99;
    int ret = admin.verifyExists(10);
    if(ret==0)
        cout<<"\nInvalid admin choice test case passed\n";
    else
        cout<<"\nInvalid admin choice test case failed\n";
}

void Tests::testValidChoiceAdmin()    //Tests for a Valid choice by admin
{
    admin.menu_rows[1] = 0.99;
    int ret = admin.verifyExists(1);
    if(ret==1)
        cout<<"\nValid admin choice test case passed\n";
    else
        cout<<"\nValid admin choice test case failed\n";
}

void Tests::testInvalidNameAdmin()  //Tests for an invalid item name by admin
{
    int ret;
    ret = admin.verifyInput("dfjgsmjdfbhjsmdfhbvjsmdfbv","0.22");
    if(ret==1)
        cout<<"\nInvalid admin item name test case passed\n";
    else
        cout<<"\nInvalid admin item name test case failed\n";
}

void Tests::testInvalidPriceAdmin() //Tests for an invalid item price by admin
{
    int ret;
    ret = admin.verifyInput("dada","helloworld");
    if(ret==2)
        cout<<"\nInvalid admin item price test case passed\n";
    else
        cout<<"\nInvalid admin item price test case failed\n";
}

void Tests::testValidNameAdmin()    //Tests for a valid name by admin
{
    int ret;
    ret = admin.verifyInput("hello","0.22");
    if(ret==0)
        cout<<"\nValid admin item name test case passed\n";
    else
        cout<<"\nValid admin item name test case failed\n";
}

void Tests::testBadCardNumber()     //Tests for a card number that doesn't fit the requirements
{
    string cnum = "1234";
    string exp = "10/22";
    string cvv = "123";
    int ret = pay.verifyCard(cnum,exp,cvv);
    if(ret==0)
        cout<<"\nBad card number test case passed\n";
    else
        cout<<"\nBad card number test case failed\n";
}

void Tests::testExpiryDateError()   //Tests for an invalid expiry date
{
    string cnum = "1234123412341234";
    string exp = "15/25";
    string cvv = "123";
    int ret = pay.verifyCard(cnum,exp,cvv);
    if(ret==0)
        cout<<"\nExpiry date error test case passed\n";
    else
        cout<<"\nExpiry date error test case failed\n";
}

void Tests::testCVVError()      //Tests for a CVV format error
{
    string cnum = "1234123412341234";
    string exp = "10/22";
    string cvv = "12";
    int ret = pay.verifyCard(cnum,exp,cvv);
    if(ret==0)
        cout<<"\nCVV error test case passed\n";
    else
        cout<<"\nCVV error test case failed\n";
}

void Tests::testValidCardDetails()  //Tests for a valid card
{
    string cnum = "1234123412341234";
    string exp = "10/22";
    string cvv = "123";
    int ret = pay.verifyCard(cnum,exp,cvv);
    if(ret==1)
        cout<<"\nValid card details test case passed\n";
    else
        cout<<"\nValid card details test case failed\n";
}

#ifndef TESTS_H_INCLUDED
#define TESTS_H_INCLUDED
#include "main.h"

class Tests
{
private:
    Customer cust;
    Admin admin;
    Chef chef;
    PaymentStrategy pay;
    UserLogin *user;
public:
    Tests()
    {
        user = user->getInstance();
    }
    void runAllTests(MYSQL* conn);
    void AdminTests();
    void ChefTests();
    void CustomerTests();
    void LoginTests(MYSQL* conn);
    void testInvalidUsername();
    void testPasswordMismatch(MYSQL* conn);
    void testPasswordLength(MYSQL* conn);
    void testInvalidChoice();
    void testValidOrder();
    void testValidChoice();
    void testEmptyOrder();
    void testInvalidOrder();
    void testInvalidChoiceChef();
    void testValidChoiceChef();
    void testInvalidChoiceAdmin();
    void testValidChoiceAdmin();
    void testInvalidNameAdmin();
    void testInvalidPriceAdmin();
    void testValidNameAdmin();
    void testBadCardNumber();
    void testExpiryDateError();
    void testCVVError();
    void testValidCardDetails();
};

#endif // TESTS_H_INCLUDED

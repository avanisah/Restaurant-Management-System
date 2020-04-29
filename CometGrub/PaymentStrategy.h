#ifndef PAYMENTSTRATEGY_H_INCLUDED
#define PAYMENTSTRATEGY_H_INCLUDED

#include "main.h"

using namespace std;

//Strategy pattern class

class PaymentStrategy
{
private:
    int cashPayment()   //Strategy 1
    {
        string pass;
        cout<<"Enter the cashier password (Ask your cashier to enter it once you've completed the payment):\n";
        cin>>pass;
        if(pass == "CometGrubPass")
        {
            cout<<"Amount paid in cash."<<endl;
            return 1;
        }
        else return 0;
    }

    int cardPayment()  //Strategy 2
    {
        string cardnum,exp,cvv;
        cout<<"\nEnter the card number:";
            cin>>cardnum;
            cout<<"\nEnter the expiry date (MM/YY):";
            cin>>exp;
            cout<<"\nEnter the CVV:";
            cin>>cvv;
            if(verifyCard(cardnum,exp,cvv)==1)
            {
                cout<<"Amount paid using card"<<endl;
                return 1;
            }
            else
                return 0;
    }

public:
    int paymentStrategy(int choice) //Strategy selection function
    {
        int resp;
        switch(choice)
        {
        case 1:
            resp = cashPayment();
            break;
        case 2:
            resp = cardPayment();
            break;
        default:
            resp = -1;
        }
        return resp;
    }

    int verifyCard(string cardnum, string exp, string cvv) //Checks if card details are valid
    {
        regex card("[0-9]{16}");
        regex expiry("(0[1-9]|10|11|12)\/[0-9][0-9]");
        regex cvvm("[0-9]{3}");
        if(regex_match(cardnum,card))
        {
            if(regex_match(exp,expiry))
            {
                if(regex_match(cvv,cvvm))
                {
                    return 1;
                }
            }
        }
        return 0;
    }

};

#endif // PAYMENTSTRATEGY_H_INCLUDED

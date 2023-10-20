#include "CreditAccount.h"
#include <iostream>

CreditAccount::CreditAccount()
{
    accountBalance = 10000.0f;
}
void CreditAccount::Withdraw(float amount)
{
    if (amount <= 40)
    {
        BaseAccount::Withdraw(amount);
    }

    else
    {
        std::cout << "You've withdrawn more than $40 and so you've incurred a $5000 surcharge" << std::endl;
        BaseAccount::Withdraw(amount + 5000);
    }
}
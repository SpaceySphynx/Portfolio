#include "CheckingAccount.h"
#include <iostream>

CheckingAccount::CheckingAccount()
{
    accountBalance = 1000.0f;
}
void CheckingAccount::Withdraw(float amount)
{
    if (numberOfWithdrawals >= 10) 
    {
        amount += 5;
        std::cout << "You've made more than 10 withdraws and so you've been charged a $5 fee." << std::endl;
    }
    BaseAccount::Withdraw(amount);
}
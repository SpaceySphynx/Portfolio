#include "SavingsAccount.h"
#include <iostream>

SavingsAccount::SavingsAccount()
{
    accountBalance = 2000.0f;
}
void SavingsAccount::Withdraw(float amount)
{
    if (numberOfWithdrawals < 3)
    {
        BaseAccount::Withdraw(amount);
    }

    else
    {
        std::cout << "Withdrawal not allowed. Maximum of 3 withdrawals reached." << std::endl;
    }
}
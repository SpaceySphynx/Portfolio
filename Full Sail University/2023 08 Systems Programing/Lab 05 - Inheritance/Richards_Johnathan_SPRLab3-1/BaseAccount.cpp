#include "BaseAccount.h"
#include <iostream>

void BaseAccount::Withdraw(float amount)
{
    if (amount > 0)                         // Make sure the amount is positive
    {
        if (amount <= accountBalance)       // Make sure the amount is available in the balance
        {
            accountBalance -= amount;       // Decrease the balance by the amount
            numberOfWithdrawals++;          // Increment the number of withdrawals
        }
        else
        {
            std::cout << "Insufficient funds." << std::endl;
        }
    }
    else 
    {
        std::cout << "Amount must be greater than zero" << std::endl;
    }

}

void BaseAccount::Deposit(float amount)
{
    if (amount > 0)                     // Make sure the amount is positive
    {
        accountBalance += amount;       // Increase the balance by the amount
    }

    else
    {
        std::cout << "Amount must be greater than zero" << std::endl;
    }
}

float BaseAccount::GetBalance() const
{
	return accountBalance;
}
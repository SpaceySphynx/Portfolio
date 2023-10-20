#pragma once
#include "BaseAccount.h"
// SavingsAccount Header
class SavingsAccount:public BaseAccount
{
public:
	SavingsAccount();
	void Withdraw(float amount) override;
};

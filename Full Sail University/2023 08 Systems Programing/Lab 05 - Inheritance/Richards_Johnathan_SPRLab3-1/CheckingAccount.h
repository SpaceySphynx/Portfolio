#pragma once
#include "BaseAccount.h"
// CheckingAccount Header
class CheckingAccount:public BaseAccount
{
public:
	CheckingAccount();
	void Withdraw(float amount) override;
};


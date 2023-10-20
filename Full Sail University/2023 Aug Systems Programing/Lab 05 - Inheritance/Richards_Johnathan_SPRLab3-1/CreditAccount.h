#pragma once
#include "BaseAccount.h"
// CreditAccount Header
class CreditAccount:public BaseAccount
{
public:
	CreditAccount();
	void Withdraw(float amount) override;
};


#pragma once
// Header file for BaseAccount
class BaseAccount
{
	// protected variables set to 0
protected:
	float accountBalance = 0.0f;
	int numberOfWithdrawals = 0;
	// public declaring functions
public:

	virtual void Withdraw(float amount);
	virtual void Deposit(float amount);
	virtual float GetBalance() const;
};


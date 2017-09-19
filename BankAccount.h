#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>

class BankAccount {
	std::string ActNum;
	std::string FirstName;
	std::string LastName;
	double balance;

	bool isInteger(const std::string & text) const;

public:
	BankAccount();
	BankAccount(const std::string & actN, const std::string & fname, const std::string & lname, double bal);

	void deposit(double money);

	const std::string toString() const;
	void print(std::ostream & out = std::cout) const; // FIXME

	// Setters
	void setAccountNumber(const std::string & actN);
	void setLastName(const std::string & lname);

	// Getters
	std::string getAccountNumber() const;
	const std::string getFirstName() const;
	const std::string getLastName() const;
	const std::string getFullName() const;
	double getBalance() const;
};


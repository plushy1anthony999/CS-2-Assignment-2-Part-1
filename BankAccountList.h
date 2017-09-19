#pragma once
#include <iostream>
#include "BankAccount.h"

// Tells whether the List array	in BankAccountList Class is currently sorted
enum class LIST_STATE_FLAGS { UNSORTED, SORTED_BY_ACCOUNT, SORTED_BY_LASTNAME, SORTED_BY_BALANCE }; 


class BankAccountList {
	const static int MAX = 30;

	BankAccount List[MAX];
	int list_state; 
	int num_elements; // Number of active elelments in List[] i.e. its logical length

public:
	BankAccountList();

	// Getters
	const std::string getFirstName(const std::string & actNum) const;
	const std::string getLastName(const std::string & actNum) const;
	const std::string getFullName(const std::string & actNum) const;
};


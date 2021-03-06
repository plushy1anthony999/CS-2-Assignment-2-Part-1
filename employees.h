#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include "Employee.h"

const int MAX_NUM_OF_EMPLOYEES = 30;

enum class EMPLOYEE_SORT_FLAGS { ID, LAST_NAME, GROSS_SALARY };


class Employees { // Container that holds an array of Employee Objects created from a txt file
	Employee employees[MAX_NUM_OF_EMPLOYEES];
	size_t employeesLength = 0;

	void sortByID(); // Swap employees in array in ascending order based on IdNumber
	void sortByLastName(); // Swap employees in array in ascending order based on lastName
	void sortByGrossSalary(); // Swap employees in array in ascending order based on grossSalary
public:
	// Pass in an opened input-txt-file to read employee info from
	// Will write info to internal array
	Employees(const std::string filename, std::ifstream & employeeDataFile);

	Employee getEmployeeByIndex(unsigned int index) const;
	Employee getEmployeeByLastName(std::string lastName) const;
	Employee getEmployeeByID(unsigned int ID) const;

	size_t getEmployeesLength() const;

	// Will modify the employees array and sort it based on "lastName", "ID", or "grossSalary" using Bubble Sort
	void sort(EMPLOYEE_SORT_FLAGS SORT_FLAG);

	// Pass in an opened output-txt-file to write all employees info formatted as a table
	void writeToFile(std::ofstream & outFile) const;
	// Will write to console all employees formatted in a table
	void writeToConsole(std::ostream & console) const;
};



#include <assert.h>
#include <sstream>
#include "Employee.h"
#include "Employees.h"
#include "BankAccount.h"

using namespace std;

void doUnitTesting();
void testEmployeeClass();
void testEmployeesClass();
void testBankAccountClass(); // FIXME - Add tests for print()

template <typename T>
bool promptForValue(T & value, string promptMessage = "", string errorMessage = "");

const bool UNIT_TESTING = true;



int main() {
	if (UNIT_TESTING) doUnitTesting();

	/* Read in Employee Info input file */
	string inputFileName;

	promptForValue(inputFileName, "Please provide an input file to read from: ");

	ifstream infile(inputFileName);

	Employees employees(inputFileName, infile);

	if (employees.getEmployeesLength() == 0) // Exit Program if input file is empty
		return 0;

	// Create Output Files
	ofstream outfile("outFile.txt");

	// Write Unsorted Employees to Output Files	
	cout << "Writing Employee Info to File \"outfile.txt\"..." << endl;
	outfile << "Unsorted Employees: " << endl << endl;
	employees.writeToFile(outfile);

	outfile << endl;
	

	// Employees sorted by ID
	employees.sort(EMPLOYEE_SORT_FLAGS::ID);
	outfile << "Employees sorted by ID: " << endl << endl;
	employees.writeToFile(outfile);
	outfile << endl;

	// Employees sorted by Last Name
	employees.sort(EMPLOYEE_SORT_FLAGS::LAST_NAME);
	outfile << "Employees sorted by Last Name: " << endl << endl;
	employees.writeToFile(outfile);
	outfile << endl;

	// Employees sorted by Gross Salary
	employees.sort(EMPLOYEE_SORT_FLAGS::GROSS_SALARY);
	outfile << "Employees sorted by Gross Salary: " << endl << endl;
	employees.writeToFile(outfile);
	outfile << endl;

	/* Display User Menu */
	while (true) {

		cout << "----------------------------------------------------------" << endl;
		cout << "1. Search for an employee by their ID Number" << endl;
		cout << "2. Search for an employee by their Last Name (if more than one is found, only the first one is returned)" << endl;
		cout << "3. Quit" << endl;
		cout << endl;

		int menuOption;
		cout << "Enter your choice: ";

		if (!promptForValue(menuOption)) { // Bad input given
			cout << "Please select a number from 1 to 3" << endl << endl;
			continue; // Display menu again
		}

		switch (menuOption) {
		case 1: {
			int employeeIdNumber;
			cout << "Enter the employee's ID Number: ";

			if (!promptForValue(employeeIdNumber)) { // Bad input given
				cout << "Invalid ID Number Given" << endl << endl;
				continue; // Display menu again
			}

			Employee employee = employees.getEmployeeByID(employeeIdNumber);
			if (employee.getIsEmptyEmployee()) {
				cout << "An employee with ID " << employeeIdNumber << " could not be found." << endl << endl;
				continue;
			}
			else {
				employee.writeToConsole(cout);
				cout << endl;
				continue;
			}
			 
			cout << endl;
			continue;

		}

		case 2: {
			string employeeLastName;
			cout << "Enter the employee's last name: ";

			if (promptForValue(employeeLastName)) {
				Employee employee = employees.getEmployeeByLastName(employeeLastName); // If last name couldn't be found, an empty employee is created

				if (employee.getIsEmptyEmployee()) {
					cout << "The employee \"" << employeeLastName << "\" could not be found." << endl << endl;
					continue;
				}
				else {
					employee.writeToConsole(cout);
					cout << endl;
					continue;
				}
			}
			else
				cout << "Invalid last name given" << endl;
			
			continue;
		}

		case 3:
			return 0; // Quit the Program

		default:
			cout << "Please select a number from 1 to 3" << endl << endl;
			continue;
		}
	}
}


void doUnitTesting() {
	cout << "Starting Unit Tests..." << endl;
	cout << "----------------------------------------------------" << endl;
	testEmployeeClass();
	testEmployeesClass();
	testBankAccountClass();
	
	cout << "All tests passed" << endl;
	cout << "-----------------------------------------------------" << endl;
}

void testEmployeeClass() {
	/* Test Employee Class */
	cout << "Testing the Employee Class..." << endl;
	Employee employee_1 = Employee(
		"Anthony",
		"Ghouri",
		'M',
		1000,
		3,
		12,
		4
	);

	Employee employee_2 = Employee(
		"Emily",
		"Ghouri",
		'S',
		1001,
		3,
		50,
		1
	);

	// Test Employee Getter Methods
	assert(employee_1.getFirstName() == "Anthony");
	assert(employee_1.getLastName() == "Ghouri");
	assert(employee_1.getEmployeeCode() == 'M');
	assert(employee_1.getIdNumber() == 1000);
	assert(employee_1.getClassificationCode() == 3);
	assert(employee_1.getYearsOfService() == 12);
	assert(employee_1.getEducationalCode() == 4);
	assert(employee_1.getJobType() == "Management");
	assert(employee_1.getEmployeeBasePay() == EMPLOYEE_CODE_M_BASE_PAY);
	assert(employee_1.getGrossSalary() == 2205);
	assert(employee_1.getIsValidEmployee() == true);

	assert(employee_2.getFirstName() == "Emily");
	assert(employee_2.getLastName() == "Ghouri");
	assert(employee_2.getEmployeeCode() == 'S');
	assert(employee_2.getIdNumber() == 1001);
	assert(employee_2.getClassificationCode() == 3);
	assert(employee_2.getYearsOfService() == 50);
	assert(employee_2.getEducationalCode() == 1);
	assert(employee_2.getJobType() == "Factory Worker");
	assert(employee_2.getEmployeeBasePay() == EMPLOYEE_CODE_S_BASE_PAY);
	assert(employee_2.getGrossSalary() == 1320);

	cout << endl;
}
void testEmployeesClass() {
	cout << "Testing the Employees Class..." << endl;

	ifstream inputFile1("namelist.txt");
	ifstream inputFile2("namelist2.txt");
	ifstream inputFile3("namelist3.txt");

	Employees employeesContainer[] = {
		Employees("namelist.txt", inputFile1),
		Employees("namelist2.txt", inputFile2),
		Employees("namelist3.txt", inputFile3)
	};

	// Test "namelist.txt"

	// Before Sorting
	assert(employeesContainer[0].getEmployeeByIndex(0).getLastName() == "Smith");
	assert(employeesContainer[0].getEmployeeByIndex(0).getFirstName() == "Jeff");
	assert(employeesContainer[0].getEmployeeByIndex(0).getEmployeeCode() == 'M');
	assert(employeesContainer[0].getEmployeeByIndex(0).getIdNumber() == 1234);
	assert(employeesContainer[0].getEmployeeByIndex(0).getClassificationCode() == 3);
	assert(employeesContainer[0].getEmployeeByIndex(0).getYearsOfService() == 12);
	assert(employeesContainer[0].getEmployeeByIndex(0).getEducationalCode() == 2);
	assert(employeesContainer[0].getEmployeeByIndex(0).getJobType() == "Management");
	assert(employeesContainer[0].getEmployeeByIndex(0).getEmployeeBasePay() == EMPLOYEE_CODE_M_BASE_PAY);
	assert(employeesContainer[0].getEmployeeByIndex(0).getGrossSalary() == 1980);

	// After Sorting by ID
	employeesContainer[0].sort(EMPLOYEE_SORT_FLAGS::ID);

	assert(employeesContainer[0].getEmployeeByIndex(1).getLastName() == "Summer");
	assert(employeesContainer[0].getEmployeeByIndex(1).getFirstName() == "Jeff");
	assert(employeesContainer[0].getEmployeeByIndex(1).getEmployeeCode() == 'M');
	assert(employeesContainer[0].getEmployeeByIndex(1).getIdNumber() == 1294);
	assert(employeesContainer[0].getEmployeeByIndex(1).getClassificationCode() == 3);
	assert(employeesContainer[0].getEmployeeByIndex(1).getYearsOfService() == 22);
	assert(employeesContainer[0].getEmployeeByIndex(1).getEducationalCode() == 3);
	assert(employeesContainer[0].getEmployeeByIndex(1).getJobType() == "Management");
	assert(employeesContainer[0].getEmployeeByIndex(1).getEmployeeBasePay() == EMPLOYEE_CODE_M_BASE_PAY);
	assert(employeesContainer[0].getEmployeeByIndex(1).getGrossSalary() == 2235);

	// After Sorting by Last Name
	employeesContainer[0].sort(EMPLOYEE_SORT_FLAGS::LAST_NAME);

	assert(employeesContainer[0].getEmployeeByIndex(0).getLastName() == "Adam");
	assert(employeesContainer[0].getEmployeeByIndex(0).getFirstName() == "John");
	assert(employeesContainer[0].getEmployeeByIndex(0).getEmployeeCode() == 'O');
	assert(employeesContainer[0].getEmployeeByIndex(0).getIdNumber() == 6703);
	assert(employeesContainer[0].getEmployeeByIndex(0).getClassificationCode() == 3);
	assert(employeesContainer[0].getEmployeeByIndex(0).getYearsOfService() == 42);
	assert(employeesContainer[0].getEmployeeByIndex(0).getEducationalCode() == 3);
	assert(employeesContainer[0].getEmployeeByIndex(0).getJobType() == "Office Worker");
	assert(employeesContainer[0].getEmployeeByIndex(0).getEmployeeBasePay() == EMPLOYEE_CODE_O_BASE_PAY);
	assert(employeesContainer[0].getEmployeeByIndex(0).getGrossSalary() == 1690);

	// After Sorting by Gross Salary
	employeesContainer[0].sort(EMPLOYEE_SORT_FLAGS::GROSS_SALARY);

	assert(employeesContainer[0].getEmployeeByIndex(0).getIsValidEmployee() == false); // All invalid employees should have invalid Gross Salaries
																					   // and so should be first in the array
	assert(employeesContainer[0].getEmployeeByIndex(0).getGrossSalary() == -1);


	// Find and test against the first Valid Employee
	for (size_t i = 0; i < employeesContainer[0].getEmployeesLength(); i++) {
		if (employeesContainer[0].getEmployeeByIndex(i).getIsValidEmployee()) {
			assert(employeesContainer[0].getEmployeeByIndex(i).getLastName() == "Khan");
			assert(employeesContainer[0].getEmployeeByIndex(i).getFirstName() == "Jack");
			assert(employeesContainer[0].getEmployeeByIndex(i).getEmployeeCode() == 'S');
			assert(employeesContainer[0].getEmployeeByIndex(i).getIdNumber() == 23414);
			assert(employeesContainer[0].getEmployeeByIndex(i).getClassificationCode() == 2);
			assert(employeesContainer[0].getEmployeeByIndex(i).getYearsOfService() == 5);
			assert(employeesContainer[0].getEmployeeByIndex(i).getEducationalCode() == 2);
			assert(employeesContainer[0].getEmployeeByIndex(i).getJobType() == "Factory Worker");
			assert(employeesContainer[0].getEmployeeByIndex(i).getEmployeeBasePay() == EMPLOYEE_CODE_S_BASE_PAY);
			assert(employeesContainer[0].getEmployeeByIndex(i).getGrossSalary() == 960);

			break;
		}
	}


	// Test Employees Getter Methods
	Employee employeeById = employeesContainer[0].getEmployeeByID(6703);
	assert(employeeById.getLastName() == "Adam");
	assert(employeeById.getFirstName() == "John");
	assert(employeeById.getEmployeeCode() == 'O');
	assert(employeeById.getIdNumber() == 6703);
	assert(employeeById.getClassificationCode() == 3);
	assert(employeeById.getYearsOfService() == 42);
	assert(employeeById.getEducationalCode() == 3);
	assert(employeeById.getJobType() == "Office Worker");
	assert(employeeById.getEmployeeBasePay() == EMPLOYEE_CODE_O_BASE_PAY);
	assert(employeeById.getGrossSalary() == 1690);
}

void testBankAccountClass() {
	cout << "Testing the BankAccount Class..." << endl;
	BankAccount bankAccount1;
	BankAccount bankAccount2("123", "Anthony", "Ghouri", 10);
	BankAccount bankAccount3("12", "George", "Washington", -1);

	// Test Getters
	assert(bankAccount1.getAccountNumber() == "Account Number not set");
	assert(bankAccount1.getFirstName() == "First Name not set");
	assert(bankAccount1.getLastName() == "Last Name not set");
	assert(bankAccount1.getFullName() == "First Name not set Last Name not set");
	assert(bankAccount1.getBalance() == 0);
	assert(bankAccount2.getAccountNumber() == "123");
	assert(bankAccount2.getFirstName() == "Anthony");
	assert(bankAccount2.getFullName() == "Anthony Ghouri");
	assert(bankAccount2.getBalance() == 10);
	assert(bankAccount3.getAccountNumber() == "12");
	assert(bankAccount3.getBalance() == 0);

	// Test Setters
	bankAccount1.setAccountNumber("1");
	assert(bankAccount1.getAccountNumber() == "1");
	bankAccount1.setAccountNumber("");
	assert(bankAccount1.getAccountNumber() == "1");
	bankAccount2.setLastName("Smith");
	assert(bankAccount2.getFullName() == "Anthony Smith");

	// Test toString()
	stringstream sstream;
	sstream << left << setw(20) << "Name" << setw(20) << "Account Number" << setw(16) << "Current Balance" << endl;
	sstream << left << setw(20) << "Anthony Smith" << setw(20) << "123" << '$' << setw(16) << fixed << setprecision(2) << (double)10;

	// Test deposit()
	bankAccount1.deposit(-1);
	assert(bankAccount1.getBalance() == 0);
	bankAccount1.deposit(100);
	assert(bankAccount1.getBalance() == 100);
	bankAccount1.deposit(10);
	assert(bankAccount1.getBalance() == 110);

	// Test withdraw()
	bankAccount1.withdraw(0);
	assert(bankAccount1.getBalance() == 110);
	bankAccount1.withdraw(-10);
	assert(bankAccount1.getBalance() == 110);
	bankAccount1.withdraw(120);
	assert(bankAccount1.getBalance() == 110);
	bankAccount1.withdraw(103);
	assert(bankAccount1.getBalance() == 7);

	//cout << sstream.str() << endl;
	//cout << bankAccount2.toString() << endl;
	assert(bankAccount2.toString() == sstream.str());

	// Test print() w/ cout

	// Test print() w/ output-file
	ofstream outfile("BankAccount_toString()_Test.txt");
	bankAccount1.print(outfile);
}

template <typename T>
bool promptForValue(T & value, string promptMessage, string errorMessage) {

	string strInput;

	if (!promptMessage.empty())
		cout << promptMessage;

	getline(cin, strInput); // Read user input as string
	stringstream sstreamInput(strInput); // turns the string into a stream

	// Checks for complete conversion to the return type T
	if (
		sstreamInput >> value &&
		!(sstreamInput >> strInput) // Make sure that no garbage is left in sstreamInput
	)
		return true;
	else {
		cin.clear(); // just in case if cin entered a bad state

		if(!errorMessage.empty())
			cout << errorMessage << endl;

		return false;
	}
}
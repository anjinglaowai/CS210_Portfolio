//============================================================================
// Name        : CompoundInterest.cpp
// Student     : Bryan Dugan
// Course      : CS-210-H6018
// Assignment  : 5-1: Project Two Submission
// Description : Compound Interest Calculator
//============================================================================

#include <iostream>
#include <iomanip>
#include "CompoundInterest.h"


using namespace std;


struct InterestCase { // Structure to hold data for compound interest case

	double initDeposit;
	double monthlyDeposit;
	double rate;
	double months;
};


class CompoundInterest {

	private:

		InterestCase interestCase; // Structure for holding input data



	public:

		CompoundInterest() {}; // Default constructor


		CompoundInterest(double init, double monthly, double interest, double years) { // Case-building constructor

			InterestCase intCase;
			intCase.initDeposit = init;
			intCase.monthlyDeposit = monthly;
			intCase.rate = interest;
			intCase.months = years * 12.0; // Converts years input to months
			interestCase = intCase;

		}


		~CompoundInterest() {}; // Destructor


		void CalculateInterestWithDeposits(InterestCase &intCase) {

			double initial = intCase.initDeposit;
			double monthlyDep = intCase.monthlyDeposit;
			double monthlyIntDecimal = (intCase.rate / 100) / 12.0;
			double monthlyTotalDep= monthlyDep + initial;
			double monthlyIntTotal = monthlyIntDecimal * monthlyTotalDep;
			double monthEndBal = monthlyTotalDep + monthlyIntTotal;
			double months = intCase.months;
			unsigned i;
			int year = 1;
			double intTotalYear = monthlyIntTotal; // Holder for incrementing yearly total interest accrued each month. Will reset to 0 every 12 months.

			cout << "\n\n\n";
			cout << "   Balance and Interest WITH Additional Monthly Deposits" << endl;
			cout << "========================================================================" << endl;
			cout << "\t" << "YEAR\tYEAR END BALANCE\t\tYEAR END EARNED INTEREST" << endl;
			cout << "------------------------------------------------------------------------" << endl;

			for (i = 1; i <= months; ++i) {  // Loop to calculate monthly interest, increment end balance, and display yearly data

				if (i % 12 == 0) {  // Displays data for each year, once 12 months have incremented
					cout << "\t" << fixed << right << setprecision(2) << setfill (' ') << setw (4) << year;
					cout << "\t" << fixed << right<< setprecision(2) << setfill (' ') << setw (16) << monthEndBal;
					cout << "\t\t\t" << fixed << setprecision(2) << setfill (' ') << setw (16) << intTotalYear << endl;

					year += 1;
					intTotalYear = 0;

				}
				// Iterative calculations and incrementing for each loop pass.

				monthlyIntTotal = (monthEndBal + monthlyDep) * monthlyIntDecimal;

				monthEndBal += (monthlyIntTotal + monthlyDep);

				intTotalYear += monthlyIntTotal;


			}
		}


		void CalculateInterestWithoutDeposits(InterestCase &intCase) {

			double initial = intCase.initDeposit;
			double monthlyIntDecimal = (intCase.rate / 100) / 12.0;
			double monthlyIntTotal = monthlyIntDecimal * initial;
			double monthEndBal = initial + monthlyIntTotal;
			double months = intCase.months;
			unsigned i;
			int year = 1;
			double intTotalYear = monthlyIntTotal; // Holder for incrementing yearly total interest accrued each month. Will reset to 0 every 12 months.

			cout << "\n\n\n";
			cout << "   Balance and Interest WITHOUT Additional Monthly Deposits" << endl;
			cout << "========================================================================" << endl;
			cout << "\t" << "YEAR\tYEAR END BALANCE\t\tYEAR END EARNED INTEREST" << endl;
			cout << "------------------------------------------------------------------------" << endl;

			for (i = 1; i <= months; ++i) { // Loop to calculate monthly interest, increment end balance, and display yearly data

				if (i % 12 == 0) { // Displays data for each year, once 12 months have incremented
					cout << "\t" << fixed << right << setprecision(2) << setfill (' ') << setw (4) << year;
					cout << "\t" << fixed << right<< setprecision(2) << setfill (' ') << setw (16) << monthEndBal;
					cout << "\t\t\t" << fixed << setprecision(2) << setfill (' ') << setw (16) << intTotalYear << endl;

					year += 1; // Increments year for next output at multiple of 12 months
					intTotalYear = 0; // Resets intTotalYear for a new year of incrementing

				}
				// Iterative calculations and incrementing for each loop pass.

				monthlyIntTotal = (monthEndBal) * monthlyIntDecimal;

				monthEndBal += monthlyIntTotal;

				intTotalYear += monthlyIntTotal;


			}
		}


		InterestCase GetInterestCase(){ // Accessor for interestCase object
			return interestCase;
		}


		double GetInput(){ // adapted from to answer at https://stackoverflow.com/a/3274025
			// Ensures that user input is of type double before allowing user to move on to next input
			double input;

			while (1) {

			  if (cin >> input) { // Break back to main for next input
			      // Valid number
			      break;
			  }
			  else {
			      // Not a valid number
				  cout << "\nPlease enter a valid number.\n";
			      cin.clear();
			      while (cin.get() != '\n') ; // Empty loop
			  }
			}
			return input;
		}


		void InputVerification(){ // adapted from to answer at https://stackoverflow.com/a/3274025
			// Ensures that user input is of type char and a valid y/n or Y/N, before displaying compound interest calculations
			char ok;

			while (1) {

				if (cin >> ok){
					// Valid char
					if (ok == 'y' || ok == 'Y'){ // Break back to main for compound interest calculations display.
						break;
					}
					else if (ok == 'n' || ok == 'N'){ // Exit if data incorrect
						cout << "\nExiting app..." << endl;
						exit(0);
					}
				}

			cout << "Please enter a valid response (y/n or Y/N):";
			cin.clear();

			while (cin.get() != '\n') ; // Empty loop

			}

		}

};



int main() {

	CompoundInterest compInt; // Instance of CompoundInsterest class
	InterestCase TestCase; // Instance of InterestCase structure
	double inputDeposit;
	double inputMonthly;
	double interestRate;
	double numberYears;


	cout << "**********************************************************" << endl;
	cout << "********************** Data Input ************************" << endl;

	cout << "Initial Deposit Amount: $";
	inputDeposit = compInt.GetInput();

	cout << "Monthly Deposit Amount: $";
	inputMonthly = compInt.GetInput();

	cout << "Annual Interest: ";
	interestRate = compInt.GetInput();

	cout << "Number of years: ";
	numberYears = compInt.GetInput();

	compInt = CompoundInterest(inputDeposit, inputMonthly, interestRate, numberYears); // Load TestCase data

	cout << "Is this okay? (y / n) : ";
	compInt.InputVerification();

	TestCase = compInt.GetInterestCase();
	compInt.CalculateInterestWithoutDeposits(TestCase);
	compInt.CalculateInterestWithDeposits(TestCase);

	exit(0);

	return 0;

}

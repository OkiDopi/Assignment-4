#include <iostream>
#include <string>
//a class constructor for the date!
class Date {
//private section has variables which the date is constructed of. 
private:
	
	std::string monthString;
	int month;
	int day;
	int year;

public:
	//function that sets the date! Input conditions are the month, day and year! It then takes these values and stores them into the private variables stored in the class! 
	void setDate(int setMonth = 1, int setDay = 1, int setYear = 2001) {
		
		const std::string arrMonths[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

		if (!validateDate(setMonth, setDay, setYear)) {

			monthString = arrMonths[0];
			month = 1;
			day = 1;
			year = 2001;
			return;

		}
		else {
			
			monthString = arrMonths[setMonth-1];
			month = setMonth;
			day = setDay;
			year = setYear;

		}

	}
	//basic accessor function that grabs the day of the date.
	int sayDay() {
		return day;
	}
	//basic accessor function that grabs the month of the date.
	std::string sayMonth() {
		return monthString;
	}
	//basic accessor function that grabs the year of the date.
	int sayYear() {
		return year;
	}
	//utility function to print out all of the data as a single compact date!
	void printDate() {
		std::cout << monthString << " " << day << " " << year << "\n";
	}
	//date validation function that goes through each condition in where the user's date input would be invalid and returns true if it's all good, and false if it's all bad.
	bool validateDate(int setMonth, int setDay, int setYear) {

		if (setMonth < 1 || setMonth > 12) {

			return false;
		}
		if (setDay < 1) {

			return false;
		}
		if (setYear < 1) {

			return false;
		}
		else if ((setMonth == 1 || setMonth == 3 || setMonth == 5 || setMonth == 7 || setMonth == 8 || setMonth == 10 || setMonth == 12) && setDay > 31) {

			return false;

		}
		else if ((setMonth == 4 || setMonth == 6 || setMonth == 9 || setMonth == 11) && setDay > 30) {

			return false;

		}
		else if (setMonth == 2 && setDay > 28 && !isLeapYear(setYear)) {

			return false;

		}
		else if (setMonth == 2 && setDay > 29 && isLeapYear(setYear)) {

			return false;

		}
		else {

			return true;

		}
	};
	//function that checks if the year input to it is a leap year or not through the power of breaking down the year and modulo'ing each section (thanks google, my original implimentation was taking the date, subtracting 2000, and modulo'ing 4 and seeing if there was a remainder or not). returns true oif it's a leap year and false if it isn't.
	bool isLeapYear(int year) {

		if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {

			return true;

		}
		else {

			return false;

		}

	}
	//function overload! You can choose to use this in the validatedate section and it will instead of putting something into the parameter section, will reference the variable stored into the year section in the private section of the class!
	bool isLeapYear() {

		if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {

			return true;

		}
		else {

			return false;

		}

	}

};
//here's main
int main() {
	//creates a date that should work.
	Date birthday;
	birthday.setDate(1, 29, 2002);
	birthday.printDate();
	//creates a purposefully facetious date class, used this to debug the validation function.
	Date error;
	error.setDate(2, 33, 2006);
	error.printDate();

	return 0;

}

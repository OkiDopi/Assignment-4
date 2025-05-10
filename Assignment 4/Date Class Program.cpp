#include <iostream>
#include <string>
#include <cmath>
//a class constructor for the date!
class Date {
//private section has variables which the date is constructed of. 
private:
	
	std::string monthString;
	int month;
	int day;
	int year;
	const std::string arrMonths[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

public:
	//prefix operator overload for ++ that adds a day to the date!
	Date& operator++() {

		day++;
		if (!validateDate(month, day, year)) {
			day = 1;
			month++;
			if (!validateDate(month, day, year)) {
				month = 1;
				year++;
			}
		}
		monthString = arrMonths[month - 1];

		return *this;

	}
	//postfix
	Date operator++(int) {

		Date oldDate = *this;

		day++;
		if (!validateDate(month, day, year)) {
			day = 1;
			month++;
			if (!validateDate(month, day, year)) {
				month = 1;
				year++;
			}
		}
		monthString = arrMonths[month - 1];

		return oldDate;
	}
	//prefix operator overload for -- that subtracts a day to the date!
	Date& operator--() {

		day--;
		if (!validateDate(month, day, year)) {
			day = 1;
			month--;
			if (!validateDate(month, day, year)) {
				month = 12;
				year--;
			}

			day = monthToDays(month, year);

		}
		monthString = arrMonths[month - 1];
		return *this;
	}
	//postfix
	Date operator--(int) {

		Date oldDate = *this;

		day--;
		if (!validateDate(month, day, year)) {
			day = 1;
			month--;
			if (!validateDate(month, day, year)) {
				month = 12;
				year--;
			}

			day = monthToDays(month, year);

		}
		monthString = arrMonths[month - 1];
		return oldDate;
	}
	//operator overload to find the distance in days between two dates.
	int operator-(Date other) {
		int daysFirst = this->day;
		int monthsFirst = this->month;
		int yearsFirst = this->year;
		int firstDateDays = 0;

		int daysSecond = other.day;
		int monthsSecond = other.month;
		int yearsSecond = other.year;
		int secondDateDays = 0;

		for (int i = monthsFirst - 1; i > 0; i--) {

			firstDateDays = firstDateDays + monthToDays(monthsFirst, yearsFirst);

		}

		for (int i = yearsFirst - 1; i > 0; i--) {
		
			firstDateDays = firstDateDays + yearToDays(yearsFirst);
		
		}

		firstDateDays = firstDateDays + daysFirst;

		for (int i = monthsSecond - 1; i > 0; i--) {

			secondDateDays = secondDateDays + monthToDays(monthsSecond, yearsSecond);

		}

		for (int i = yearsSecond - 1; i > 0; i--) {

			secondDateDays = secondDateDays + yearToDays(yearsSecond);

		}

		secondDateDays = secondDateDays + daysSecond;

		return std::abs(secondDateDays - firstDateDays);

	}
	//operator overload for << to print out a formatted date.
	friend std::ostream& operator<<(std::ostream& string, Date& date) {
	
		string << date.arrMonths[date.month - 1] << " " << date.day << ", " << date.year;
		return string;
	
	}
	//operator overload for >> to ask the user to input a date to create a new date object. 
	friend std::istream& operator>>(std::istream& string, Date& date) {

		std::cout << "Enter a day" << "\n";
		string >> date.day;
		std::cout << "Enter a month" << "\n";
		string >> date.month;
		std::cout << "Enter a year" << "\n";
		string >> date.year;

		return string;
	
	}

	//function that sets the date! Input conditions are the month, day and year! It then takes these values and stores them into the private variables stored in the class! 
	void setDate(int setMonth = 1, int setDay = 1, int setYear = 2001) {

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
	static bool isLeapYear(int year) {

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
	//function that converts a month to days. takes in a month and the year associated with that year and converts it to days.
	int monthToDays(int month, int year) {

		if (month == 1 || month == 3 || month == 7 || month == 8 || month == 10 || month == 12) {

			return 31;

		}
		else if (month == 9 || month == 4 || month == 6 || month == 11) {

			return 30;

		}
		else if (month == 2 && Date::isLeapYear(year)) {

			return 29;

		}
		else if (month == 2 && !Date::isLeapYear(year)) {

			return 28;
		}
		else {

			return 0;

		}
	}
	//function that converts years to days. intakes a year and returns the amount of days in that year.
	int yearToDays(int year) {

		if (Date::isLeapYear(year)) {

			return 366;

		}
		else {

			return 365;

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
	error.setDate(13, 45, 2018);
	error.printDate();
	error.setDate(4, 31, 2000);
	error.printDate();
	error.setDate(2, 29, 2009);
	error.printDate();
	//creates dummy date to test an edge case that would run through all of the logic for the - operator overload. 
	Date test;
	test.setDate(1, 1, 2005);
	//runs through the test date to test edge cases and the functionality of the overloaded operators
	test++;
	test.printDate();
	test--;
	test--;
	test.printDate();
	//tests the overloaded - operator
	birthday.setDate(4, 10, 2014);
	test.setDate(4, 18, 2014);
	std::cout << (birthday - test);
	std::cout << "\n";
	birthday.setDate(2, 2, 2006);
	test.setDate(11, 10, 2003);
	std::cout << (birthday - test);
	std::cout << "\n";
	birthday.setDate(2, 29, 2008);
	birthday++;
	birthday.printDate();
	birthday--;
	birthday.printDate();

	//tests the overloaded << and >> operators.
	Date userinput;
	std::cin >> userinput;
	std::cout << userinput;
	
	std::cin.get();

	return 0;

}


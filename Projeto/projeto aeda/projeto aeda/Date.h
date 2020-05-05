#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <sstream>
#include <cmath>



using namespace std;



class Date {
private:
	unsigned short day;
	unsigned short month;
	unsigned year;

public:
	Date() :day(0), month(0), year(0) {};
	Date(string date);
	Date(unsigned short day, unsigned short month, unsigned year);

	// GET methods
	/**
	*@brief get method
	*/
	unsigned short getDay() const { return day; }
	/**
	*@brief get method
	*/
	unsigned short getMonth() const { return month; }
	/**
	*@brief get method
	*/
	unsigned getYear() const { return year; }

	// SET methods
	/**
	*@brief set method
	*/
	void setDay(unsigned short day) { this->day = day; };
	/**
	*@brief set method
	*/
	void setMonth(unsigned short month) { this->month = month; };
	/**
	*@brief set method
	*/
	void setYear(unsigned year) { this->year = year; };

	// other methods */


	bool operator<(Date d) {
		if (year < d.getYear())return true;
		if (year > d.getYear())return false;
		if (month < d.getMonth())return true;
		if (month > d.getMonth())return false;
		if (day < d.getDay())return true;
		return false;
	}

	bool operator==(Date d) {
		if (year == d.getYear() && month == d.getMonth() && day == d.getDay())return true;
		return false;
	}
	Date operator+(Date d);
	Date operator+(int i);
	friend ostream& operator<<(ostream& out, const Date& date);

};


class InvalidDates {
	Date* beg;
	Date* end;
public:
	InvalidDates(Date* b, Date* e) :beg(b), end(e) {};
	/**
	*@brief get method
	*/
	Date* getInvalidBegDate() { return beg; }
	/**
	*@brief get method
	*/
	Date* getInvalidEndDate() { return end; }
};



#include "Date.h"
#include "Extra_functions.h"



using namespace std;




Date::Date(string date) {

	vector<string> aux;
	//cout << date;
	aux = decompose(date, '/');
	this->day = mstoi(aux.at(0));
	this->month = mstoi(aux.at(1));
	this->year = mstoi(aux.at(2));

}


Date::Date(unsigned short day, unsigned short month, unsigned year) {

	this->day = day;
	this->month = month;
	this->year = year;
}

ostream& operator<<(ostream& out, const Date& date) {
	string d = "";
	string m = "";
	if (date.getDay() < 10) d = "0" + to_string(date.getDay());
	else d = to_string(date.getDay());
	if (date.getMonth() < 10) m = "0" + to_string(date.getMonth());
	else m = to_string(date.getMonth());
	out << d << "/" << m << "/" << date.getYear();
	return out;
}

Date Date::operator+(Date d) {
	int y = year + d.getYear();
	int m = month + d.getMonth();
	int da = day + d.getDay();
	Date date(da, m, y);
	if (!checkDate(new Date(da, m, y))) date = correctDate(date);
	return date;
}



Date Date::operator+(int i) {
	int y = year;
	int m = month;
	int d = day + i;
	Date date(d, m, y);
	if (!checkDate(new Date(d, m, y))) date = correctDate(date);
	return date;

}



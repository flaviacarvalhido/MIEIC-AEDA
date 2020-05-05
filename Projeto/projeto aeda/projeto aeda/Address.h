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
//#include "Extra_functions.h"


using namespace std;

struct Time {
	int hour;
	int min;

	Time() = default;
	Time(string s);
	Time(int hour, int min) :hour(hour) {
		this->min = min;
	};

	Time operator+(Time t);
	bool operator<(Time t) {
		if (hour < t.hour)return true;
		if (hour > t.hour)return false;
		return min < t.min;

	}
};

class Address {

	string street;/**<the street*/
	string nr;/**<the number of the door or other info if there is no door number*/
	string zip;/**<the zip*/
	string municipality;/**<the minucipality*/

public:
	/**
	*@brief constructor
	*/
	Address():street(""),nr(""),zip(""),municipality("") {};
	/**
	*@brief constructor
	*/
	Address(string street, string nr, string zip, string m) :street(street), nr(nr), zip(zip), municipality(m) {};
	/**
	*@brief constructor
	*/
	Address(string m);
	/**
	*@brief destructor
	*/
	~Address() = default;
	/**
	*@brief set method
	*/
	void setStreet(string s) { this->street = s; };
	/**
	*@brief get method
	*/
	string getStreet() const { return street; }
	/**
	*@brief set method
	*/
	void setNumber(string n) { this->nr = n; };
	/**
	*@brief get method
	*/
	string getNumber() const { return nr; }
	/**
	*@brief set method
	*/
	void setZip(string n) { this->zip = n; }
	/**
	*@brief get method
	*/
	string getZip() const { return zip; }
	/**
	*@brief set method
	*/
	void setMunicipality(string m) { this->municipality = m; };
	/**
	*@brief get method
	*/
	string getMunicipality() const{ return municipality; }
	/**
	*@brief Operator <<
	*@param address - address being streamed
	*@return a ostream with the address
	*/
	friend ostream& operator<<(ostream& out, Address& address);
};





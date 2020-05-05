#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <sstream>
#include <cmath>
#include "Address.h"
#include "Extra_functions.h"


using namespace std;

Time::Time(string s) {
	vector<string> parts = decompose(s, ':');
	hour = stoi(parts.at(0));
	min = stoi(parts.at(1));
}


Time Time::operator+(Time t) {
	int h = hour;
	int m = min;
	h += t.hour;
	m += t.min;
	if (m >= 60) {
		h += 1;
		m -= 60;
	}
	else if (m < 0) {
		h -= 1;
		m += 60;
	}


	if (h >= 24) {
		h -= 24;
	}
	else if (h < 0) {
		h += 24;
	}
	return Time(h, m);
}





Address::Address(string m) {
	vector<string> parts = decompose(m, ',');
	//cout<< m;
	this->street = parts.at(0);
	this->nr = parts.at(1);

	this->zip = parts.at(2);
	this->municipality = parts.at(3);
}

ostream& operator<<(ostream& out, Address& address) {
	string street = address.getStreet();
	//accentPlace(street);
	string mun = address.getMunicipality();
	//accentPlace(mun);
	out << street << ", " << address.getNumber() << ", " << address.getZip() << ", " << mun;
	return out;
}
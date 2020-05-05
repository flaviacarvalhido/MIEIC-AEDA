#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "Address.h"
#include "Extra_functions.h"

using namespace std;

class Tech {
	pair<Time,Date> avai;
	int manu;
	string name;

public:


	Tech(string name) : name(name), manu(0) { 
		//avai.first = currentTimeNDate().first; avai.second = currentTimeNDate().second;
	};
	Tech(string name, int manu, pair<Time, Date> avai) :name(name), manu(manu), avai(avai) {};
	void setName(string name) { this->name = name; }
	string getName() const{ return name; }

	void setManu(int manu) { this->manu = manu; }
	void addManu() { 
		manu++;
	}
	int getManu() const{ return manu; }

	void setAvai(pair <Time,Date>) { this->avai = avai; }
	pair <Time,Date> getAvai() const{ return avai; }

	bool operator < ( Tech T) const ;

};

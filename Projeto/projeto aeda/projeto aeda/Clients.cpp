
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <sstream>
#include <cmath>
#include "Extra_functions.h"
#include "Clients.h"
#include "Employees.h"
#include "Util.h"


using namespace std;


float Client::totalSpent() {
	float result = 0;
	for (auto a : orders) {
		if (a->getOk())result += a->getPrice();
	}
	return result;
}
/*
void Client::orderViewer() {

	for (unsigned int i = 0; i < orders.size(); i++) {

		cout << "ID: " << orders[i]->getId() << endl;
		cout << "Deliverer: " << orders[i]->getDeliverer()->getName() << endl;
		cout << "Restaurant: " << orders[i]->getRestaurant()->getName() << endl;
		cout << "Products: " << endl;
		for (unsigned int j = 0; j < orders[i]->getProducts().size(); j++) {
			cout << "	" << orders[i]->getProducts()[j].first->getName() << "    Quantity: " << orders[i]->getProducts()[j].second << endl;
		}
		cout << "Price: " << orders[i]->getPrice() << endl;
		cout << "Date: " << *orders[i]->getDate() << endl;
		cout << endl;

	}

}
*/

void Client::orderViewer() {
	unsigned int times = orders.size() / 3;
	unsigned int extra = orders.size() % 3;
	unsigned int i = 0;
	int o1 = 0;
	int o2 = 0;
	int o3 = 0;
	long long minus = 0; //to remove warning
	long long nr = 38;
	for (unsigned int j=0 ; j < times; j++) {

		cout << "ID: " << orders[i]->getId();
		cout << setw(40-to_string(orders[i]->getId()).length()) << "ID: " << orders[i+1]->getId();
		cout << setw(40-to_string(orders[i + 1]->getId()).length()) << "ID: " << orders[i+2]->getId() << endl;
		cout << "Deliverer: " << orders[i]->getDeliverer()->getName();
		cout << setw(40- orders[i]->getDeliverer()->getName().length()) << "Deliverer: " << orders[i+1]->getDeliverer()->getName();
		cout << setw(40- orders[i + 1]->getDeliverer()->getName().length()) << "Deliverer: " << orders[i+2]->getDeliverer()->getName() << endl;
		cout << "Restaurant: " << orders[i]->getRestaurant()->getName();
		cout << setw(40 - orders[i]->getRestaurant()->getName().length()) << "Restaurant: " << orders[i+1]->getRestaurant()->getName();
		cout << setw(40 - orders[i + 1]->getRestaurant()->getName().length()) << "Restaurant: " << orders[i+2]->getRestaurant()->getName() << endl;
		cout << "Products: ";
		cout << setw(40) << "Products: ";
		cout << setw(40) << "Products: " << endl;
		for (unsigned int k = 0; k < max(max(orders[i]->getProducts().size(), orders[i + 1]->getProducts().size()), orders[i + 2]->getProducts().size()); k++) {
			if (o1 == 0) {
				cout << " -" << orders[i]->getProducts()[k].first->getName() << " x" << orders[i]->getProducts()[k].second;
				minus= (long long) orders[i]->getProducts()[k].first->getName().length() + to_string(orders[i]->getProducts()[k].second).length();
				if (k == orders[i]->getProducts().size() - 1) o1 = 1;
			}
			else if (o1 == 1) minus = -5;
			if (o2 == 0) {
				cout << setw((nr - minus)) << "-" << orders[i + 1]->getProducts()[k].first->getName() << " x" << orders[i + 1]->getProducts()[k].second;
				minus = (long long) orders[i+1]->getProducts()[k].first->getName().length() + to_string(orders[i+1]->getProducts()[k].second).length();
				if (k == orders[i + 1]->getProducts().size() - 1) o2 = 1;
			}
			else if (o2 == 1) minus = -5;
			
			if (o3 == 0) {
				cout << setw((nr - minus)) << "-" << orders[i + 2]->getProducts()[k].first->getName() << " x" << orders[i + 2]->getProducts()[k].second << endl;
				if (k == orders[i + 2]->getProducts().size() - 1) o3 = 1;
			}
			else if (o3 == 1)cout << endl;
		}
		cout << "Price: " << fixed<<setprecision(2)<<orders[i]->getPrice();
		cout << setw(35) << "Price: "<< fixed << setprecision(2) <<orders[i + 1]->getPrice();
		cout << setw(35) << "Price: " << fixed << setprecision(2) << orders[i + 2]->getPrice() << endl;
		cout << "Date: " << *orders[i]->getDate();
		cout << setw(30) << "Date: " << *orders[i + 1]->getDate();
		cout << setw(30) << "Date: " << *orders[i + 2]->getDate() << endl;
		cout << endl;


		o1 = 0;
		o2 = 0;
		o3 = 0;
		i += 3;
	}
	if (extra == 2) {
		cout << "ID: " << orders[i]->getId();
		cout << setw(40 - to_string(orders[i]->getId()).length()) << "ID: " << orders[i + 1]->getId() << endl;
		cout << "Deliverer: " << orders[i]->getDeliverer()->getName();
		cout << setw(40 - orders[i]->getDeliverer()->getName().length()) << "Deliverer: " << orders[i + 1]->getDeliverer()->getName() << endl;
		cout << "Restaurant: " << orders[i]->getRestaurant()->getName();
		cout << setw(40 - orders[i]->getRestaurant()->getName().length()) << "Restaurant: " << orders[i + 1]->getRestaurant()->getName() << endl;
		cout << "Products: ";
		cout << setw(40) << "Products: " << endl;
		for (unsigned int k = 0; k < max(orders[i]->getProducts().size(), orders[i + 1]->getProducts().size()); k++) {
			if (o1 == 0) {
				cout << " -" << orders[i]->getProducts()[k].first->getName() << " x" << orders[i]->getProducts()[k].second;
				minus = (long long) orders[i]->getProducts()[k].first->getName().length() + to_string(orders[i]->getProducts()[k].second).length();
				if (k == orders[i]->getProducts().size() - 1) o1 = 1;
			}
			else if (o1 == 1) minus = -5;
			if (o2 == 0) {
				cout << setw((nr - minus)) << "-" << orders[i + 1]->getProducts()[k].first->getName() << " x" << orders[i + 1]->getProducts()[k].second << endl;
				if (k == orders[i + 1]->getProducts().size() - 1) o2 = 1;
			}
			else if (o2 == 1)cout << endl;

		}
		cout << "Price: " << orders[i]->getPrice();
		cout << setw(35) << "Price: " << fixed << setprecision(2) << orders[i + 1]->getPrice() << endl;
		cout << "Date: " << *orders[i]->getDate();
		cout << setw(30) << "Date: " << *orders[i + 1]->getDate() << endl;

		cout << endl;
	}
	else if (extra == 1) {
		cout << "ID: " << orders[i]->getId() << endl;
		cout << "Deliverer: " << orders[i]->getDeliverer()->getName() << endl;
		cout << "Restaurant: " << orders[i]->getRestaurant()->getName() << endl;
		cout << "Products: " << endl;
		for (unsigned int j = 0; j < orders[i]->getProducts().size(); j++) {
			cout << "	" << orders[i]->getProducts()[j].first->getName() << "    Quantity: " << orders[i]->getProducts()[j].second << endl;
		}
		cout << "Price: " << fixed << setprecision(2) << orders[i]->getPrice() << endl;
		cout << "Date: " << *orders[i]->getDate() << endl;
		cout << endl;
	}





}



/*
void Client::orderViewer() {
	unsigned int times = orders.size() / 2;
	unsigned int extra = orders.size() % 2;
	unsigned int i = 0;
	int o1 = 0;
	int o2 = 0;
	int minus = 0;
	for (unsigned int j = 0; j < times; j++) {

		cout << "ID: " << orders[i]->getId();
		cout << setw(40 - to_string(orders[i]->getId()).length()) << "ID: " << orders[i + 1]->getId() << endl;
		cout << "Deliverer: " << orders[i]->getDeliverer()->getName();
		cout << setw(40 - orders[i]->getDeliverer()->getName().length()) << "Deliverer: " << orders[i + 1]->getDeliverer()->getName() << endl;
		cout << "Restaurant: " << orders[i]->getRestaurant()->getName();
		cout << setw(40 - orders[i]->getRestaurant()->getName().length()) << "Restaurant: " << orders[i + 1]->getRestaurant()->getName() << endl;
		cout << "Products: ";
		cout << setw(40) << "Products: " << endl;
		for (unsigned int k = 0; k <  max(orders[i]->getProducts().size(), orders[i + 1]->getProducts().size()); k++) {
			if (o1 == 0) {
				cout << " -" << orders[i]->getProducts()[k].first->getName() << " x" << orders[i]->getProducts()[k].second;
				minus = orders[i]->getProducts()[k].first->getName().length() + to_string(orders[i]->getProducts()[k].second).length();
				if (k == orders[i]->getProducts().size() - 1) o1 = 1;
			}
			else if (o1 == 1) minus = -5;
			if (o2 == 0) {
				cout << setw(38 - minus)<<"-" << orders[i + 1]->getProducts()[k].first->getName() << " x" << orders[i + 1]->getProducts()[k].second << endl;
				if (k == orders[i + 1]->getProducts().size() - 1) o2 = 1;
			}
			else if (o2 == 1)cout << endl;

		}
		cout << "Price: " << orders[i]->getPrice();
		cout << setw(45-to_string(orders[i]->getPrice()).length())<<"Price: " << orders[i+1]->getPrice() << endl;
		cout << "Date: " << *orders[i]->getDate();
		cout << setw(30)<<"Date: " << *orders[i+1]->getDate() << endl;

		cout << endl;


		o1 = 0;
		o2 = 0;
		i += 2;
	}

	if (extra == 1) {
		cout << "ID: " << orders[i]->getId() << endl;
		cout << "Deliverer: " << orders[i]->getDeliverer()->getName() << endl;
		cout << "Restaurant: " << orders[i]->getRestaurant()->getName() << endl;
		cout << "Products: " << endl;
		for (unsigned int j = 0; j < orders[i]->getProducts().size(); j++) {
			cout << " -" << orders[i]->getProducts()[j].first->getName() << " x" << orders[i]->getProducts()[j].second << endl;
		}
		cout << "Price: " << orders[i]->getPrice() << endl;
		cout << "Date: " << *orders[i]->getDate() << endl;
		cout << endl;
	}
}
*/

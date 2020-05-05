
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



int Deliverer::succefulDeliveries() const{
	int result = 0;
	for (auto a : history) if (a->getOk())result++;
	return result;
}

float Deliverer::moneyMade(Date* beg, Date* end) const{
	if (!isDateValid(beg, end)) throw InvalidDates(beg, end);
	float result = 0;
	for (auto a : history) {
		if (a->getOk()) {
			if ((*beg < *a->getDate()) && (*a->getDate() < *end)) {
				if (a->getRestaurant()->getAddress()->getMunicipality() == a->getClient()->getAddress()->getMunicipality()) {
					result += 3 + (a->getPrice() - 3) / 10;
				}
				else result += 5 + (a->getPrice() - 5) / 10;
			}
		}
	}
	return result;
}




void Deliverer::updateRating() {
	float result = 0;
	int counter = 0;
	for (auto a : history) {
		if (a->getRated()) {
			counter++;
			result += a->getRating();
		}
	}
	if (counter) this->medRating = result / counter;
	else this->medRating = 3;
}






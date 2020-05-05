
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <sstream>
#include <cmath>
#include <queue>

#include "Extra_functions.h"
#include "Clients.h"
#include "Employees.h"
#include "Util.h"
#include "Base.h"
#include <stdlib.h>
#include "Sort_methods.h"
#include "Tech.h"




using namespace std;
Company::Company(string filename) {
	vector<Base*> bases;
	vector<Client*> c;
	vector<Restaurant*> r;
	vector<Delivery*> d;
	vector<string> parts;
	string temp;
	int counter=0;
	ifstream a_file;
	a_file.open(filename);
	Base b;
	while(getline(a_file, temp)) {
		//cout << " b "<<temp;
		
		switch(counter){
		case 0:
			parts = decompose(temp, ' ');
			b.setMunicipality(parts.at(1));
			break;
		case 1:
			b.setAddress(temp);
			break;
		case 2:
			b.setCoordinates(temp);
			break;
		case 3:
			b.setNeighbouring(decompose(temp,','));
			break;
		case 4:
			b.setRestaurantFile(temp);
			b.setRestaurants(b.extract_restaurants(temp));
			break;
		case 5:
			b.setClientFile(temp);
			c = b.extract_clients(temp);
			b.setClients(c);
			c = b.extract_blacklist(temp);
			b.setBlacklist(c);
			break;
		case 6:
			b.setEmployeeFile(temp);
			b.setEmployees(b.extract_employees(temp));
			b.extractVehicles();
			b.setVehicleTree();
			break;
		case 7:
			b.setDeliveryFile(temp);
			b.setDeliveries(b.extract_deliveries(temp));
			b.updateDeliveries();
			break;
		case 8:
			b.setTechFile(temp);
			b.extract_techs(temp);
			break;
		case 9:
			
				bases.push_back(new Base(b));
				b = Base();
				counter = -1;
				break;
			
		}
		counter++;
	}

	//b.extractVehicles();

	a_file.close();
	this->bases = bases;
	this->BaseFile = filename;
}



vector<Client*>Base::extract_clients(string filename) {

	vector<Client*> clients;
	Client c;
	ifstream a_file;
	a_file.open(filename);
	string temp;
	int counter = 0;
	int nif = 0;
	while (getline(a_file, temp)) {
		
		switch (counter) {
		case 0:
			replaceAccent(temp);
			//cout << temp;
			c.setName(temp);
			break;
		case 1:
			c.setAddress(temp);
			c.setMunicipality(c.getAddress());
			break;
		case 2:
			//cout << "nif" << temp;
			nif = mstoi(temp);
			//cout << "-" << nif;
			c.setNif(nif);
			break;
		case 3:
			c.setPassword(temp);
			break;
		case 4:
			if (compare_str(temp, "erased")) c.setErased(true);
			else c.setErased(false);
			break;
		case 5:
			clients.push_back(new Client(c));
			if (temp == "__________") {
				a_file.close();
				return clients;
			}
			counter = -1;
			break;
		}
		counter++;
	}
	a_file.close();
	return clients;
}

vector<Client*>Base::extract_blacklist(string filename) {
	vector<Client*> blacklist;
	Client c;
	ifstream a_file;
	a_file.open(filename);
	string temp;
	int counter = 0;
	do { getline(a_file, temp); 
	} while (temp != "__________"); //clears the other clients
	while (getline(a_file, temp)) {
		//scout << temp;
		
		switch (counter) {
		case 0:
			replaceAccent(temp);
			c.setName(temp);
			break;
		case 1:
			c.setAddress(temp);
			c.setMunicipality(c.getAddress());
			break;
		case 2:
			c.setNif(stoi(temp));
			break;
		case 3:
			c.setPassword(temp);
			break;
		case 4:
			if (compare_str(temp, "erased")) c.setErased(true);
			else c.setErased(false);
			break;
		case 5:
			
				blacklist.push_back(new Client(c));
				counter = -1;
				break;
			
		}
		counter++;
	}
	
	a_file.close();
	return blacklist;
}

vector<Restaurant*>Base::extract_restaurants(string filename) {
	vector<Restaurant*> rest;
	Restaurant r;
	string temp;
	int counter = 0;
	ifstream a_file;
	a_file.open(filename);
	vector<string>parts;
	Time t;
	while (getline(a_file, temp)) {
		//cout << " r " << temp;
		
		switch (counter) {
		case 0:
			replaceAccent(temp);
			r.setName(temp);
			break;
		case 1:

			r.setAddress(temp);
			break;
		case 2:
			r.setProducts(temp);
			break;
		case 3:
			parts = decompose(temp, ':');
			t.hour = mstoi(parts.at(0));
			t.min = mstoi(parts.at(1));
			r.setClose(t);
			break;
		case 4:
			if (compare_str(temp, "inactive"))r.setInactive(true);
			else r.setInactive(false);
			break;
		case 5:
			rest.push_back(new Restaurant(r));
			counter = -1;
			break;
			
		}
		counter++;

	}
	
	a_file.close();
	return rest;
}


vector<Delivery*>Base::extract_deliveries(string filename) {

	vector<Delivery*> deliveries;
	Delivery d;
	int counter = 0;
	string temp;
	ifstream a_file;
	a_file.open(filename);
	vector<string> parts;
	vector<string> parts2;
	//Restaurant r;
	vector<pair<Product*,int>> p;

	Deliverer* dr;
	while (getline(a_file, temp)) {
		
		switch (counter) {
		case 0:
			d.setId(mstoi(temp));
			break;
		case 1:
			parts = decompose(temp, '-');
			dr = new Deliverer (findEmployee(mstoi(parts.at(1))));
			d.setDeliverer(dr); //need to solve the Employee/Deliverer problem
			break;
		case 2:
			parts = decompose(temp, '-');
			//cout << parts.at(1);

			try {
				d.setClient(findClient(mstoi(parts.at(1))));
			}
			catch (NoClientWithSuchNif & e) {
				cout << "NoClientWithSuchNif: client not found" << endl << endl;

			}
			break;
		case 3:
			trim(temp);

			try {
				d.setRestaurant(findRestaurant(temp));
			}
			catch (NoRestaurantWithSuchName & e) {
				cout << "NoRestaurantWithSuchName: couldn't find restaurant" << endl;
			}

			break;
		case 4:
			parts = decompose(temp, ',');
			for (auto a : parts) {
				parts2 = decompose(a, '/');
				//cout << "erro-" << temp;
				p.push_back(make_pair(d.getRestaurant()->findProduct(parts2[0]),mstoi(parts2[1])));
			}
			d.setProducts(p);
			p.clear();
			break;
		case 5:
			parts = decompose(temp, '-');
			d.setTime(parts.at(0));
			d.setDate(new Date(parts.at(1)));
			break;
		case 6:
			d.setPrice(stof(temp));
			break;
		case 7:
			parts = decompose(temp, '-');
			if (compare_str(parts.at(0),"ok")) d.setOk(true);
			else d.setOk(false);
			d.setOccurrence(parts.at(1));
			break;
		case 8:
			if (!compare_str(temp, "No rating")) {
				d.setRated(true);
				d.setRating(stof(temp));
			}
			else {
				d.setRated(false);
				d.setRating(0);
			}
			break;
		case 9:
			
				deliveries.push_back(new Delivery(d));
				counter = -1;
				break;
			
		}
		counter++;
	}
	
	a_file.close();
	return deliveries;
}


priority_queue<Tech> Base::extract_techs(string filename)
{
	priority_queue<Tech> q;
	vector<string> parts,parts2;
	string temp;
	Tech t("a");
	Time h;
	pair<Time, Date> p;
	int counter = 0;
	ifstream a_file;
	a_file.open(filename);

	while (getline(a_file, temp)) {

		switch (counter) {
		case 0:
			replaceAccent(temp);
			t.setName(temp);
			//cout << temp << endl;
			break;
		case 1:
			t.setManu(stoi(temp));
			break;
		case 2:
			parts = decompose(temp, '-');
			parts2 = decompose(parts[0], ':');
			//h.hour = stoi(parts2[0]);
			//h.min = stoi(parts2[1]);
			//p.first = h;
			//p.second = Date(parts[1]);

			t=Tech(t.getName(),t.getManu(),make_pair(Time(mstoi(parts2[0]),mstoi(parts2[1])),Date(parts[1])));
			break;
		case 3:
			counter = -1;
			q.push(t);
			break;
		}
		counter++;
	}

	a_file.close();

	techies = q;

	return q;
}
vector<Employee*>Base::extract_employees(string filename) {
	vector<Employee*> emp;
	string temp;
	int counter = 0;
	Vehicle v;
	ifstream a_file;
	a_file.open(filename);
	vector<string>parts,parts2,parts3;
	Time h;
	pair<Time, Date> pa = currentTimeNDate();
	

	Employee e;
	bool isdeliverer = false;
	Deliverer* d;
	Admin* a;
	string job;
	vector<int> ids;
	//vector<Delivery> dv;
	while (getline(a_file, temp)) {
		
		//cout << temp;
		switch (counter) {
		case 0:
			replaceAccent(temp);
			e.setName(temp);
			break;
		case 1:

			e.setNif(stoi(temp));
			break;
		case 2:
			e.setPassword(temp);
			break;
		case 3:
			e.setDate(new Date(temp));
			break;
		case 4:
			e.setSalary(stof(temp));
			break;
		case 5:
			if (temp == "Deliverer") {
				isdeliverer = true;
			}
			else isdeliverer = false;
			break;
		case 6:
			if (isdeliverer) { 
				parts = decompose(temp, ','); 
				for (auto a : parts)ids.push_back(mstoi(a));
			}
			else job = temp;
			break;
		case 7:
			
			/*parts = decompose(temp, ',');
			v.setBrand(parts.at(0));
			v.setModel(parts.at(1));
			v.setAquisition(new Date(parts.at(2)));
			v.setKms(stoi(parts.at(3)));
			v.setNDeliveries(stoi(parts.at(4)));
	
			parts2 = decompose(parts.at(5), '-');
			parts3 = decompose(parts2.at(0), ':');
			h.hour = stoi(parts3.at(0));
			h.min = stoi(parts3.at(1));
			pa.first = h;
			pa.second = Date(parts2.at(1));
			v.setLastMain(pa);*/

			e.setVehicle(new Vehicle(temp));
			break;
		case 8:
			if (compare_str(temp, "working"))e.setWorking(true);
			else e.setWorking(false);
			break;
		case 9:
			
				counter = -1;
				if (!isdeliverer) {
					a = new Admin(e.getName(), e.getPassword(), e.getNif(), e.getDate(), e.getSalary(), job, e.getVehicle());
					emp.push_back(a);
				}
				else {

					//for (auto a : ids) dv.push_back(findDelivery(a));
					d = new Deliverer(e.getName(), e.getPassword(), e.getNif(), e.getDate(), e.getSalary(), e.getVehicle());
					emp.push_back(d);
					//dv.clear();
					//ids.clear();
				}
				break;
			
		}
		counter++;
	}
	
	a_file.close();
	return emp;
}




void Company::updateCompanyfile()const {
	ofstream newfile;
	newfile.open("newBasesFile.txt");
	for (unsigned int i = 0; i < bases.size(); i++) {
		newfile << "Base " << bases.at(i)->getMunicipality() << endl;
		newfile << bases.at(i)->getAddress() << endl;
		newfile << bases.at(i)->getCoordinates()->lat << "/" << bases[i]->getCoordinates()->lon << endl;
		for (unsigned int j = 0; j < bases.at(i)->getNeighbouring().size(); j++) if (j != bases.at(i)->getNeighbouring().size() - 1) newfile << bases.at(i)->getNeighbouring().at(j) << ", ";
		else newfile << bases.at(i)->getNeighbouring().at(j) << endl;
		newfile << bases.at(i)->getRestaurantFile() << endl;
		newfile << bases.at(i)->getClientFile() << endl;
		newfile << bases.at(i)->getEmployeeFile() << endl;
		newfile << bases.at(i)->getDeliveryFile() << endl;
		
		newfile << "::::::::::" << endl;
	}


	const char* fileName = BaseFile.c_str();
	newfile.close();
	remove(fileName);
	int i=rename("newBasesFile.txt", fileName);
	if (i == 0) return;//remove warning
}




void Base::updateClientFile()const {
	ofstream newfile;
	newfile.open("newClientFile.txt");
	for (unsigned int i = 0; i < clients.size();i++) {
		string name = clients.at(i)->getName();
		accentPlace(name);
		newfile << name << endl;
		newfile << *clients.at(i)->getAddress() << endl;
		newfile << clients.at(i)->getNif() << endl;
		newfile << clients.at(i)->getPassword() << endl;
		if (clients.at(i)->getErased()) newfile << "erased" << endl;
		else newfile << "Not erased" << endl;
		if (i == clients.size() - 1) newfile << "__________" << endl;
		else newfile << "::::::::::" << endl;
	}
	for (unsigned int i = 0; i < blacklist.size(); i++) {
		string name = blacklist.at(i)->getName();
		accentPlace(name);
		newfile << name << endl;
		newfile << *blacklist.at(i)->getAddress() << endl;
		newfile << blacklist.at(i)->getNif() << endl;
		newfile << blacklist.at(i)->getPassword() << endl;
		if (blacklist.at(i)->getErased()) newfile << "erased" << endl;
		else newfile << "Not erased" << endl;
		
		newfile << "::::::::::" << endl;
	}
	const char* fileName = client_file.c_str();
	newfile.close();
	remove(fileName);
	int i=rename("newClientFile.txt", fileName);
}


void Base::updateRestaurantFile()const {
	ofstream newfile;
	newfile.open("newRestaurantFile.txt");
	for (unsigned int i = 0; i < restaurants.size(); i++) {
		string name = restaurants.at(i)->getName();
		accentPlace(name);
		newfile << name << endl;
		newfile << *restaurants.at(i)->getAddress() << endl;
		newfile << restaurants.at(i)->printProducts() << endl;
		newfile << setw(2)<<setfill('0')<<restaurants.at(i)->getClose().hour<<":"<< setw(2) << setfill('0')<<restaurants.at(i)->getClose().min << endl;
		if (restaurants.at(i)->getInactive())newfile << "inactive" << endl;
		else newfile << "active" << endl;
		newfile << "::::::::::" << endl;
	}
	
	const char* fileName = restaurant_file.c_str();
	newfile.close();
	remove(fileName);
	int i=rename("newRestaurantFile.txt", fileName);
}


void Base::updateDeliveryFile() const {
	ofstream newfile;
	newfile.open("newDeliveryFile.txt");
	for (auto a:deliveries) {

		newfile << a->getId() << endl;
		string name = a->getDeliverer()->getName();
		accentPlace(name);
		newfile << name << " - " << a->getDeliverer()->getNif() << endl;
		name = a->getClient()->getName();
		accentPlace(name);
		newfile << name << " - " << a->getClient()->getNif() << endl;
		name = a->getRestaurant()->getName();
		accentPlace(name);
		newfile << name << endl;
		for (unsigned int j = 0; j < a->getProducts().size(); j++) if (j != a->getProducts().size() - 1) newfile << a->getProducts().at(j).first->getName() << "/" << a->getProducts().at(j).second << ", ";
		else newfile << a->getProducts().at(j).first->getName()<< "/"<<a->getProducts().at(j).second << endl;
		newfile << setw(2) << setfill('0') << a->getTime().hour << ":" << setw(2) << setfill('0') << a->getTime().min << "-" << *a->getDate() << endl;
		newfile << fixed<<setprecision(2)<<a->getPrice() << endl;
		if (a->getOk()) newfile << "ok - " << a->getOccurrence() << endl; //if ok occurrence should be ammount of tip and rating
		else newfile << "not ok - " << a->getOccurrence() << endl;
		if (a->getRated()) newfile << a->getRating()<< endl;
		else newfile << "No rating" << endl;
		newfile << "::::::::::" << endl;
	}

	const char* fileName = delivery_file.c_str();
	newfile.close();
	remove(fileName);
	int i =rename("newDeliveryFile.txt", fileName);
}

void Base::updateTechFile() const
{
	string temp="";
	ofstream newfile;
	newfile.open("newTechFile.txt");

	priority_queue<Tech> copy = techies;

	while (!copy.empty()) {
		if (compare_str(temp, copy.top().getName())) {
			copy.pop();
			continue;
		}
		newfile << copy.top().getName() << "\n";

		//cout << copy.top().getName() << endl;
		
		newfile << copy.top().getManu() << "\n";
		newfile << setw(2) << setfill('0') << copy.top().getAvai().first.hour << ":" << setw(2) << setfill('0') << copy.top().getAvai().first.min << "-" << copy.top().getAvai().second << endl;

		newfile << "::::::::::" << endl;

		temp = copy.top().getName();

		copy.pop();
	}


	newfile << "\n";

	const char* fileName = tech_file.c_str();
	newfile.close();
	remove(fileName);
	int i = rename("newTechFile.txt", fileName);

}


void Base::updateEmployeeFile() const {
	ofstream newfile;
	newfile.open("newEmployeeFile.txt");
	//sort(employees.begin(), employees.end(),importance);
	for (unsigned int i = 0; i < employees.size(); i++) {
		string name = employees.at(i)->getName();
		accentPlace(name);
		newfile << name << endl;
		newfile << employees.at(i)->getNif() << endl;
		newfile << employees.at(i)->getPassword() << endl;
		newfile << *employees.at(i)->getDate() << endl;
		newfile << employees.at(i)->getSalary() << endl;
		if (employees.at(i)->isDeliverer()) {
			newfile << "Deliverer" << endl;
			if (employees.at(i)->getHistory().size() == 0) newfile << "No deliveries made yet" << endl;
			for (unsigned int j = 0; j < employees.at(i)->getHistory().size(); j++) if (j != employees.at(i)->getHistory().size() - 1) newfile << employees.at(i)->getHistory().at(j)->getId()<< ", ";
			else newfile << employees.at(i)->getHistory().at(j)->getId() << endl;
		}
		else {
			newfile << "Admin" << endl;
			newfile << employees.at(i)->getAJob() << endl;
		}
		newfile << *employees.at(i)->getVehicle() << endl;
		if(employees.at(i)->getWorking())newfile << "Working" << endl;
		else newfile << "Not working" << endl;
		newfile << "::::::::::" << endl;
	}

	const char* fileName = employee_file.c_str();
	newfile.close();
	remove(fileName);
	int i =rename("newEmployeeFile.txt", fileName);
}




vector<Restaurant*> Base::searchByCuisine(string type) {
	vector<Restaurant*> rest;
	
	vector<Product*>p;
	vector<pair<Product*, int>> pr1;
	vector<pair<Product*, int>> pr2;
	bool check = false;
	int nr;
	sort(restaurants.begin(), restaurants.end(), mostVisited);
	int counter = 0;
	for (auto a : restaurants) {
		check = false;
		nr = a->nProdType(type);
		if (nr == 0) continue;
		else {
			
			if (rest.size() == 0) rest.push_back(a);
			else {
				for (unsigned int i = 0; i < rest.size(); i++) {
					if (nr > rest[i]->nProdType(type)) {
						rest.insert(rest.begin()+i, a);
						check = true;
						break;
					}
				}
				if (!check)rest.push_back(a);
			}
		}
		for (auto b : a->getProdNsales()) {
			if (compare_str(b.first->getType(), type)) pr1.push_back(b);
			else pr2.push_back(b);
		}
		pr1.insert(pr1.end(), pr2.begin(), pr2.end());
		for (auto b : pr1)p.push_back(b.first);
		rest.at(counter)->setProdNsales(pr1);
		rest.at(counter)->setProducts(p);
		counter++;
		p.clear();
		pr1.clear();
	}
	 
	return rest;
}
/*
void Base::insertDelivery(Delivery* d) {
	for (unsigned int i = 0; i < clients.size(); i++) {
		if (*clients.at(i) == *d->getClient()) {
			clients.at(i)->addOrder(d);
			break;
		}
	}
	for (unsigned int i = 0; i < employees.size(); i++) {
		if (employees.at(i)->getNif() == d->getDeliverer()->getNif()) {
			employees.at(i)->addDelivery(d);
			employees.at(i)->updateRating();
			break;
		}
	}
	vector<Product*> p;
	vector<pair<Product*, int>> ps;
	for (unsigned int i = 0; i < restaurants.size(); i++) {
		if (*restaurants[i] == *d->getRestaurant()) {
			restaurants[i]->incrementSales();
			ps = restaurants[i]->getProdNsales();
			for (auto b : d->getProducts()) {

				for (unsigned int i = 0; i < ps.size(); i++) {
					if (*ps.at(i).first == *b.first) {
						ps.at(i).second += b.second;
					}

				}

			}
			sort(ps.begin(), ps.end(), mostSold);
			restaurants[i]->setProdNsales(ps);
			for (auto b : ps) p.push_back(b.first);
			restaurants[i]->setProducts(p);
			ps.clear();
			p.clear();
			break;
		}
	}
	addDelivery(d);

}
*/
void Base::insertDelivery(Delivery* d) {
	unsigned int i = 0;
	//clients.at(search(d->getClient(),clients))->addOrder(d);
	for (unsigned int j = 0; j < clients.size(); j++) if (*clients.at(j) == *d->getClient()) clients.at(j)->addOrder(d);
	//i = search(new Employee(*d->getDeliverer()), employees);
	for (i = 0; i < employees.size(); i++)if (employees.at(i)->getNif() == d->getDeliverer()->getNif())break;
	employees.at(i)->addDelivery(d);
	employees.at(i)->updateRating();
	vector<Product*> p;
	vector<pair<Product*, int>> ps;
	vector<pair<string, int>> ts;
	//i = search(d->getRestaurant(), restaurants);
	for (i = 0; i < restaurants.size(); i++)if (*restaurants.at(i) == *d->getRestaurant())break;
	restaurants[i]->incrementSales();
	ps = restaurants[i]->getProdNsales();
	ts = restaurants[i]->getTypeNsales();
	for (auto b : d->getProducts()) {
		for (unsigned int j = 0; j < ps.size(); j++) {
			if (*ps.at(j).first == *b.first) {
				ps.at(j).second += b.second;
			}
		}
		for (unsigned int j = 0; j < ts.size(); j++) {
			if (compare_str(ts.at(j).first, b.first->getType())) {
				ts.at(j).second += b.second;
			}
		}
	}
	sort(ps.begin(), ps.end(), mostSold);
	sort(ts.begin(), ts.end(), tname);
	restaurants[i]->setProdNsales(ps);
	restaurants[i]->setTypeNsales(ts);
	for (auto b : ps) p.push_back(b.first);
	restaurants[i]->setProducts(p);
	
	sort(restaurants.begin(), restaurants.end(), mostVisited);
	sort(clients.begin(), clients.end(), bC);
	sort(employees.begin(), employees.end(), importance);
	deliveries.push_back(d);
}
void Base::updateDeliveries() {
	vector <Product*> p;
	vector <pair<Product*, int>> ps;
	vector <pair<string, int>> ts;
	for (auto a : deliveries) {
		for (unsigned int i = 0; i < clients.size(); i++) {
			if (*clients[i] == *a->getClient()) {
				bool check = false;
				for (auto b : clients.at(i)->getOrders()) {
					if (*b == *a) {
						check = true;
						break;
					}
				}
				if (!check)clients[i]->addOrder(a);
				break;
			}
		}
		for (unsigned int i = 0; i < employees.size(); i++) {
			
			if (employees[i]->getNif() == a->getDeliverer()->getNif()) {
				bool check = false;
				for (auto b : employees.at(i)->getHistory()) {
					if (*b == *a) {
						check = true;
						break;
					}
				}
				if (!check)employees[i]->addDelivery(a);
				break;
			}
		}
		for (unsigned int i = 0; i < restaurants.size(); i++) {
			if (*restaurants[i] == *a->getRestaurant()) {
				restaurants[i]->incrementSales();
				ps = restaurants[i]->getProdNsales();
				ts = restaurants[i]->getTypeNsales();
				for (auto b : a->getProducts()) {
					for (unsigned int j = 0; j < ts.size(); j++) {
						if (compare_str(ts.at(j).first, b.first->getType())) {
							ts.at(j).second += b.second;
						}
					}
					for (unsigned int j = 0; j < ps.size(); j++) {
						if (*ps.at(j).first == *b.first) {
							ps.at(j).second += b.second;
						}
						
					}

				}
				sort(ts.begin(), ts.end(), tname);
				sort(ps.begin(), ps.end(), mostSold);
				restaurants[i]->setProdNsales(ps);
				restaurants[i]->setTypeNsales(ts);
				for (auto b : ps) p.push_back(b.first);
				restaurants[i]->setProducts(p);
				ps.clear();
				p.clear();
				break;
			}
		}
	}
	for (unsigned int i = 0; i < employees.size(); i++) if (employees.at(i)->isDeliverer()) employees.at(i)->updateRating();
	sort(restaurants.begin(), restaurants.end(), mostVisited);
	sort(clients.begin(), clients.end(), bC);
	sort(employees.begin(), employees.end(), importance);
}
void Base::addDelivery(Delivery* d){
	for (unsigned int i = 0; i < employees.size(); i++) {
		if (d->getDeliverer() == employees[i]) {
			employees[i]->addDelivery(d);
			return;
		}
	}
	deliveries.push_back(d);
		
}

bool Base::addClient(Client* c){	
	for (auto a : blacklist) {
		if (*a == *c) { return false; }
	}

	for (unsigned int i = 0; i < neighbouring.size(); i++) {
		if (c->getAddress()->getMunicipality() == neighbouring[i] || c->getAddress()->getMunicipality() == municipality) {
			clients.push_back(c);
			return true;
		}
	}

	return false;
}

bool Base::addClientBlacklist(int nif) {
	for (auto i : blacklist)
		if (i->getNif() == nif)
			throw ClientAlreadyInBlacklist(i);
	for (unsigned int i = 0; i < clients.size(); i++) {
		if (clients[i]->getNif() == nif) {
			blacklist.push_back(clients[i]);
			clients.erase(clients.begin() + i);
			return true;
		}
	}
	throw NoClientWithSuchNif(nif);
}


float Base::moneyMade(Date* beg, Date* end) {
	float result = 0;
	//int nSal = monthsPassed(beg, end); //number of salaries that have to be paid
	//for (auto a : employees)if(a->getWorking())result -= a->getSalary() * nSal;
	for (auto a : deliveries) {
		if (a->getOk()) {
			if ((*beg < *a->getDate()) && (*a->getDate() < *end)) {
				if (a->getRestaurant()->getAddress()->getMunicipality() == a->getClient()->getAddress()->getMunicipality()) {
					result += 3 + (a->getPrice() - 3)/10;
				}
				else result += 5 + (a->getPrice() - 5)/10;
			}
		}
	}
	return result;
}

float Base::profitMade(Date* beg, Date* end) {
	float result = 0;
	int nSal = monthsPassed(beg, end); //number of salaries that have to be paid
	for (auto a : employees)if (a->getWorking())result -= a->getSalary() * nSal;
	for (auto a : deliveries) {
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


Deliverer* Base::randomDelivererGenerator() {
	vector<int> nifs;
	int usage;
	for (auto a : employees) {
		if (a->isDeliverer()) {
			if (!a->getVehicle()->getAvailable())continue;
			usage = round(a->getMedRating())*10;
			for (int i = 0; i < max(usage,20); i++) nifs.push_back(a->getNif());
		}
	}
	srand(time(NULL));
	Employee* e = findEmployee(nifs.at(rand() % nifs.size()));
	return new Deliverer(e,e->getHistory());
}


vector<string> Base::getTypesOrdered() {
	//cout << "aqui";
	vector<pair<string, int>> types;
	string prevType;
	unsigned int it=0;
	bool found;
	for (auto a : restaurants) {
		//cout << a->getTypeNsales().size() << endl;
		for (auto b : a->getTypeNsales()) {
			//cout << b.first<<endl;
			found = false;
			if (!types.size()) {
				types.push_back(b);
				prevType = b.first;
				it = 0;
			}
			else {
				if (b.first==prevType) {
					types.at(it).second += b.second;
				}
				else {
					for (unsigned int i = 0; i < types.size(); i++) {
						if (types.at(i).first==b.first) {
							it = i;
							prevType = b.first;
							types.at(i).second += b.second;
							found = true;
							break;

						}
					}
					if (!found)types.push_back(b);
				}
			}
		}
	}
	sort(types.begin(), types.end(), typeNprod);
	vector<string>rt;
	//cout << types.size();
	for (auto a : types) {
		rt.push_back(a.first);
		//cout << a.first << endl;
	}
	return rt;
}



vector<Restaurant*> Base::restaurantsLowerThan(float price) {
	vector<Restaurant*>r;
	for (auto a : restaurants) {
		if (a->medPrice() < price) r.push_back(a);
	}
	sort(r.begin(), r.end(), lowerPrice);
	return r;
}

vector<Restaurant*> Base::restaurantsHigherThan(float price) {
	vector<Restaurant*>r;
	for (auto a : restaurants) {
		if (a->medPrice() > price) r.push_back(a);
	}
	sort(r.begin(), r.end(), higherPrice);
	return r;
}



vector<Restaurant*> Base::restaurantsBetween(float p1,float p2) {
	vector<Restaurant*>r;
	for (auto a : restaurants) {
		if (a->medPrice() <p2 && a->medPrice() >p1) r.push_back(a);
	}
	sort(r.begin(), r.end(), mostVisited);
	return r;
}


void Base::sorterC() {
	sort(clients.begin(), clients.end(), bC);
}



















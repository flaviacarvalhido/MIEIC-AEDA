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
#include <queue>

#include "Date.h"
#include "Util.h"
#include "Employees.h"
#include "Clients.h"
#include "Tech.h"

#include "bst.h"

#include <unordered_set>

struct ehash {
	int operator()(Employee* e) const {
		return sumNif(e->getNif());
	}
	bool operator()(Employee* e1, Employee* e2) {
		return e1->getNif() == e2->getNif();
	}
};



typedef unordered_set<Employee*, ehash, ehash> employee_table;



using namespace std;





struct Coordinates {
	double lat;
	double lon;
};


//exceptions

class MunicipalityNotCovered : public exception{
	string m;

public:
	/**
	*@brief exception constructor
	*/
	MunicipalityNotCovered(string m) : m(m) {};
	/**
	*@brief get method
	*/
	string getMunicipalityNotCovered() { return m; }
};

class NoClientInBlacklist {
	int nif;

public:
	/**
	*@brief exception constructor
	*/
	NoClientInBlacklist( int nif) : nif(nif) {};
	/**
	*@brief get method
	*/
	int getClientNotInBlacklist() { return nif; }
};


class AlreadyInNeighbouring {
	string c;
public:
	AlreadyInNeighbouring(string c) :c(c) {};
	string getAlreadyInNeighbouring() { return c; }
};																//not implemented


class NoSuchRestaurant {
	Restaurant* r;

public:
	/**
	*@brief exception constructor
	*/
	NoSuchRestaurant(Restaurant* r) : r(r) {};
	/**
	*@brief get method
	*/
	Restaurant* getNoSuchRestaurant() { return r; }
	
};																//not implemented


class NoRestaurantWithSuchName {
	string name;
public:
	/**
	*@brief exception constructor
	*/
	NoRestaurantWithSuchName(string s) :name(s) {};
	/**
	*@brief get method
	*/
	string getNoRestaurantWithSuchName() { return name; }
};

class NoEmployeeWithSuchNif {
	int nif;
public:
	/**
	*@brief exception constructor
	*/
	NoEmployeeWithSuchNif(int nif) : nif(nif) {};
	/**
	*@brief get method
	*/
	int getNoEmployeeWithSuchNif() { return nif; }
};

class RestaurantAlreadyAffiliated {
	Restaurant* r;
public:
	RestaurantAlreadyAffiliated(Restaurant* r) :r(r) {};
	Restaurant* getRestaurantAlreadyAffiliated() { return r; }

};												//not implemented

class NoSuchClient {
	Client* c;
	

public:
	/**
	*@brief exception constructor
	*/
	NoSuchClient(Client* c) : c(c) {};
	/**
	*@brief get method
	*/
	Client* getNoSuchClient() { return c; }
	
};												//not implemented
class NoClientWithSuchNif {
	int nif;
public:
	/**
	*@brief exception constructor
	*/
	NoClientWithSuchNif(int nif) : nif(nif) {};
	/**
	*@brief get method
	*/
	int getNoClientWithSuchNif() { return nif; }
};

class NoSuchDeliveryMade {
	int id;
public:
	/**
	*@brief exception constructor
	*/
	NoSuchDeliveryMade(int id) :id(id) {};
	/**
	*@brief get method
	*/
	int getNoSuchDeliveryMadeId() { return id; }
};														//not implemented

class ClientAlreadyInBlacklist {
	Client* client;
public:
	/**
	*@brief exception constructor
	*/
	ClientAlreadyInBlacklist(Client* c) :client(c) {};
	/**
	*@brief get method
	*/
	Client* getClientAlreadyInBlacklist() { return client; }
};


class Base {
	Address* address;/**<Base's address*/
	string municipality;/**<The municipality where it is situated, also used as name*/
	Coordinates* GPS;/**<Base's gps coordinates*/
	vector <Delivery*> deliveries;/**<Overall deliveries made by this base*/
	vector <string> neighbouring;/**<Municipalities covered by this base*/
	vector <Client*> clients;/**<List of clients registered in the base*/
	vector <Client*> blacklist;/**<List of clients blacklisted in the base*/
	vector <Restaurant*> restaurants;/**<List of restaurants which the base delivers food from*/
	vector <Employee*> employees;/**<List of employees in the base*/
	vector <Vehicle *> vehicles;
	BST<Vehicle> treeVe;
	priority_queue<Tech> techies;/**<Priority queue of tech guys*/
	string client_file;/**<Name of the file where the information of the clients is stored*/
	string restaurant_file;/**<Name of the file where the information of the restaurants is stored*/
	string employee_file;/**<Name of the file where the information of the employees is stored*/
	string delivery_file;/**<Name of the file where the information of the deliveries is stored*/
	string tech_file;/**<Name of the file where the tech guys info is stored*/

public:
	/**
	*@brief default constructor
	*/
	Base() :address(new Address()), municipality(""), client_file(""), restaurant_file(""), employee_file(""), delivery_file(""), treeVe(BST<Vehicle>(Vehicle())) {
		Coordinates g;
		g.lat = 0;
		g.lon = 0;
		this->GPS = new Coordinates(g);
	};
	/**
	*@brief Base class constructor
	*@param address - Base's address
	*@param municipality - The municipality where it is situated, also used as name
	*@param gps - Base's gps coordinates
	*/
	Base(string a, string m, Coordinates* gps) : municipality(m), GPS(gps), treeVe(BST<Vehicle>(Vehicle())) {
		this->address = new Address(a);
	};
	/**
	*@brief client class destructor
	*/
	~Base()=default;

	/**
	*@brief set method
	*/
	void setCoordinates(Coordinates* gps) { this->GPS = gps; }
	/**
	*@brief set method
	*/
	void setCoordinates(double lat, double lon) {
		Coordinates gps;
		gps.lat = lat;
		gps.lon = lon;
		this->GPS = new Coordinates(gps);
	}
	/**
	*@brief set method
	*/
	void setCoordinates(string g) {
		vector <string> parts = decompose(g, '/');
		Coordinates gps;
		gps.lat = stod(parts[0]);
		gps.lon = stod(parts[1]);
		this->GPS = new Coordinates(gps);

	}
	/**
	*@brief get method
	*/
	Coordinates* getCoordinates()const { return GPS; }
	/**
	*@brief set method
	*/
	void setAddress(Address* a) { this->address = a; }
	/**
	*@brief set method
	*/
	void setAddress(string m) {
		Address* a= new Address(m);
		this->address = a;
	}
	/**
	*@brief get method
	*/
	Address* getAddress() const { return address; }
	/**
	*@brief set method
	*/
	void setMunicipality(string m) { this->municipality = m; }
	/**
	*@brief get method
	*/
	string getMunicipality() const{ return municipality; }

	/**
	*@brief set method
	*/
	void setDeliveries(vector <Delivery*> d) { this->deliveries = d; }
	/**
	*@brief adds a delivery to the deliveries vector
	*/
	void addDelivery(Delivery* d);
	/**
	*@brief get method
	*/
	vector <Delivery*> getDeliveries() const{ return deliveries; }

	/**
	*@brief set method
	*/
	void setNeighbouring(vector <string> c) { this->neighbouring = c; }
	/**
	*@brief adds a new municipality to be covered by the base
	*/
	bool addNeighbouring(string c) {
		for (auto a : neighbouring) if (a == c) throw AlreadyInNeighbouring(c);
		neighbouring.push_back(c); 
		return true;
	}
	/**
	*@brief get method
	*/
	vector <string> getNeighbouring() const{ return neighbouring; }
	/**
	*@brief deletes a municipality covered by the base (calls an exception when no municipality is found)
	*/
	void deleteNeighbouring(string m) {
		for (unsigned int i =0; i < neighbouring.size();i++) {
			if (neighbouring[i] == m) {
				neighbouring.erase(neighbouring.begin()+i);
				return;
			}
		}
		throw MunicipalityNotCovered(m);
	}
	/**
	*@brief set method
	*/
	void setClients(vector <Client*> c) { this->clients = c; }
	/**
	*@brief adds a client to thee clients vector
	*@return true if the client was added, false if the client is in the blacklist or already in the clients list
	*/
	bool addClient(Client* c);
	/**
	*@brief get method
	*/
	vector <Client*> getClients() const{ return clients; }

	/**
	*@brief set method
	*/
	void setBlacklist(vector <Client*> b) { this->blacklist = b; }
	/**
	*@brief adds a client to the blacklist
	*/
	bool addClientBlacklist(int nif);
	/**
	*@brief get method
	*/
	vector<Client*> getBlacklist() const{ return blacklist; }
	/**
	*@brief removes a client in the blacklist and adds him to the client list (throws an exception if it doesn't find the client in the blacklist)
	*/
	void ClientRedemption(int nif) {
		Client* p;
		for (unsigned i = 0; i < blacklist.size(); i++) {
			if (blacklist[i]->getNif() == nif) {
				clients.push_back(blacklist[i]);
				blacklist.erase(blacklist.begin() + i);

				return;
			}
		}

		throw NoClientInBlacklist(nif);
	}
	/**
	*@brief set method
	*/
	void setRestaurants(vector <Restaurant*> r) { this->restaurants = r; }
	/**
	*@brief adds a restaurant to the restaurants vector
	*@return true if the restaurant was successfully added and false if the restaurant was already in the vector 
	*/
	bool addRestaurant(Restaurant* r) { 
		for (auto a : restaurants) if (a == r) return false;
		restaurants.push_back(r);
		return true;
	}  
	/**
	*@brief get method
	*/
	vector <Restaurant*> getRestaurants()const{ return restaurants; }
		
	/**
	*@brief removes a restaurant from the vector (throws an exception if the restaurant is not found)
	*/
	void deleteRestaurant(Restaurant* r) {
		for (unsigned int i = 0; i < restaurants.size();i++) {
			if (restaurants[i]->getName() == r->getName()) {
				restaurants.erase(restaurants.begin()+i);
				return;
			}
		}
		throw NoSuchRestaurant(r);
	}
	/**
	*@brief set method
	*/
	void setEmployees(vector <Employee*> e) { this->employees = e; }
	
	/**
	*@brief adds a new employee to the base
	*@return false if the employee was already registered to the base, true otherwise
	*/
	bool addEmployee (Employee* e) {
		for (auto a : employees) if (a->getNif() == e->getNif()) return false;
		employees.push_back(e);
		return true;
	}
	/**
	*@brief get method
	*/
	vector <Employee*> getEmployees() const{ return employees; }
	/**
	*@brief changes the employee's working bool to false, making him unable to login the app and stopping the payment (throws an exception if the restaurant is not found)
	*/
	void deleteEmployee(int nif) {
		for (auto i : employees) {
			if (i->getNif() == nif) {
				i->setWorking(false);
				return;
			}
		}
		throw NoEmployeeWithSuchNif(nif);
	};

	void extractVehicles() {
		for (auto i : employees) {
			vehicles.push_back(i->getVehicle());
		}
		pair<Time, Date> td = currentTimeNDate();
		for (auto i : vehicles) {
			//set availability by comparing current time and last maintenance time
			if (td.second < i->getLastMain().second)i->setAvailable(false);
			else if (td.second == i->getLastMain().second && (td.first.hour - i->getLastMain().first.hour) < 4)i->setAvailable(false);
			else if (td.second == i->getLastMain().second && (td.first.hour - i->getLastMain().first.hour) >= 4)i->setAvailable(true);
			else if (td.second.getDay() - i->getLastMain().second.getDay() == 1 && (td.first<i->getLastMain().first+Time(4,0)))i->setAvailable(false);
			//else if (td.second.getDay() - i->getLastMain().second.getDay() == 1 && (i->getLastMain().first + Time(4, 0)<td.first ))i->setAvailable(true);
			else i->setAvailable(true);

		}
		
	}

	vector <Vehicle*> getVehicles() { return vehicles; }

	/**
	*@brief set method
	*/
	void setClientFile(string f) { this->client_file = f; };
	/**
	*@brief get method
	*/
	string getClientFile() const{ return client_file; }
	/**
	*@brief set method
	*/
	void setEmployeeFile(string f) { this->employee_file = f; };
	/**
	*@brief get method
	*/
	string getEmployeeFile() const{ return employee_file; }
	/**
	*@brief set method
	*/
	void setRestaurantFile(string f) { this->restaurant_file = f; };
	/**
	*@brief get method
	*/
	string getRestaurantFile() const{ return restaurant_file; }
	/**
	*@brief set method
	*/
	void setDeliveryFile(string f) { this->delivery_file = f; };
	/**
	*@brief get method
	*/
	string getDeliveryFile() const{ return delivery_file; }
	/**
	*@brief set method
	*/
	void setTechFile(string f) { this->tech_file = f; };
	/**
	*@brief get method
	*/
	string getTechFile() const { return tech_file; }



	/**
	*@brief extracts the clients information from the file
	*@param filename - the file name
	*@return a vector of clients with the information extracted
	*/
	vector<Client*> extract_clients(string filename);
	/**
	*@brief extracts the blacklisted clients information from the file
	*@param filename - the file name
	*@return a vector of blacklistedclients with the information extracted
	*/
	vector<Client*> extract_blacklist(string filename);
	/**
	*@brief extracts the restaurants information from the file
	*@param filename - the file name
	*@return a vector of restaurants with the information extracted
	*/
	vector<Restaurant*> extract_restaurants(string filename);
	/**
	*@brief extracts the employees information from the file
	*@param filename - the file name
	*@return a vector of employees with the information extracted
	*/
	vector<Employee*> extract_employees(string filename);
	/**
	*@brief extracts the deliveries information from the file
	*@param filename - the file name
	*@return a vector of delivieres with the information extracted
	*/
	vector<Delivery*> extract_deliveries(string filename);
	/**
	*@brief extracts the techs information from the file
	*@param filename - the file name
	*@return a priority_queue of techs with the information extracted
	*/
	priority_queue<Tech> extract_techs(string filename);
	
	
	
	
	/**
	*@brief adds a delivery to a client
	*@param clientnif - the client's nif to whom the delivery is going to be added
	*@param d - the delivery to be added
	*/
	void addDeliveryToClient(int clientNif, Delivery* d) { //might add exception in case the is no client with that nif
		for (unsigned int i = 0; i < clients.size();i++) {
			if (clients[i]->getNif() == clientNif) {
				clients[i]->addOrder(d);
				return;
			}
		}
	}
	/**
	*@brief adds a delivery to an employee
	*@param deliverernif - the employee's nif to whom the delivery is going to be added
	*@param d -  delivery to be added
	*/
	void addDeliveryToDeliverer(int delivererNif, Delivery* d) { //might add exception in case the is no client with that nif
		for (unsigned int i = 0; i < employees.size(); i++) {
			if (employees.at(i)->getNif() == delivererNif) {
				employees.at(i)->addDelivery(d);
				return;
			}
		}
	}
	/**
	*@brief searches for an employee with the given nif in the vector (throws an exception if it doesnt find it)
	*@param nif - the employees nif
	*@return the employee with the coresponding nif
	*/
	Employee* findEmployee(int nif) {
		for (auto a : employees) {
			//cout << "e-"<<a->getNif();
			if (a->getNif() == nif) return a;
		}
		throw NoEmployeeWithSuchNif(nif);
	}




	/**
	*@brief searches for a delivery with the given id in the vector (throws an exception if it doesnt find it)
	*@param id - the delivery id
	*@return the delivery with the coresponding id
	*/
	Delivery* findDelivery(int id) {
		for (auto a : deliveries) {
			if (a->getId() == id) return a;
		}
		throw NoSuchDeliveryMade(id);
	}
	/**
	*@brief searches for a client with the given nif in the vector (throws an exception if it doesnt find it)
	*@param nif - the client's nif
	*@return the client with the coresponding nif
	*/
	Client* findClient(int nif) {
		for (auto a : clients) {
			if (a->getNif() == nif) return a;
		}
		throw NoClientWithSuchNif(nif);
	}

	/**
	*@brief searches for a restaurant with the given name in the vector (throws an exception if it doesnt find it)
	*@param name - the restaurant's name
	*@return the restaurant with the coresponding name
	*/
	Restaurant* findRestaurant(string name) {
		for (auto a : restaurants) {
			if (a->getName() == name) return a;
		}
		throw NoRestaurantWithSuchName(name);
	}
	/**
	*@brief updates the Client file with the information changed by the program
	*/

	void updateClientFile()const;
	/**
	*@brief updates the Restaurant file with the information changed by the program
	*/
	void updateRestaurantFile()const;
	/**
	*@brief updates the Employee file with the information changed by the program
	*/
	void updateEmployeeFile()const;
	/**
	*@brief updates the Delivery file with the information changed by the program
	*/
	void updateDeliveryFile()const;


	void updateTechFile()const;


	/**
	*@brief calculates the money made by the base between the given dates (subtracts the salaries by counting the months passed)
	*@param beg - begging date
	*@param end - end date
	*@return profit made
	*/
	float moneyMade(Date* beg, Date* end);
	float profitMade(Date* beg, Date* end);
	/**
	*@brief calculates the money made by the given restaurant between the given dates
	*@param beg - begging date
	*@param end - end date
	*@param r - restaurant 
	*@return profit made
	*/
	float moneyMade(Date* beg, Date* end, Restaurant* r) {
		float total=0;
		for (auto a : deliveries) {
			if (a->getOk()) {
				if ((*beg < *a->getDate()) && (*a->getDate() < *end)) {
					if (*a->getRestaurant() == *r) total += a->getPrice();
				}
			}
			
		}
		return total;
	};
	/**
	*@brief generates a random deliverer (that works in the base) based on the medium rating 
	*@return the generated deliverer
	*/
	Deliverer* randomDelivererGenerator();
	/**
	*@brief orders the types of food by most sold 
	*@return vector with the ordered types
	*/
	vector<string> getTypesOrdered();
	/**
	*@brief gathers the restaurants with a medium price lower than the given one
	*@param price - price to be compared to
	*@return vector with the restaurants with the medium price lower than the input price
	*/
	vector<Restaurant*> restaurantsLowerThan(float price);
	/**
	*@brief gathers the restaurants with a medium price higher than the given one
	*@param price - price to be compared to
	*@return vector with the restaurants with the medium price higher than the input price
	*/
	vector<Restaurant*> restaurantsHigherThan(float price);

	/**
	*@brief gathers the restaurants with a medium price between those given
	*@param p1 - lowest price
	*@param p2 - highest price
	*@return vector with the restaurants with the medium price between the given
	*/
	vector<Restaurant*> restaurantsBetween(float p1, float p2);
	/**
	*@brief sorts the clients vector by what is considered to be the best clients
	*/
	void sorterC();

	/**
	*@brief was made into a sorting compare operator
	*/
	bool priciest(Restaurant* r1, Restaurant* r2) {
		if (r1->medPrice() < r2->medPrice()) return true;
		if ((r1->medPrice() == r2->medPrice()) && (r1->getNSales() < r2->getNSales())) return true;
		return false;

	}

	/**
	*@brief syncs the deliveries with the restaurants, clients, employees and corectly sorts them
	*/
	void updateDeliveries();
	/**
	*@brief menu used by the admin with the highest job("Boss") to employ other admins
	*@param bossW - admin information so he cant change is own salary and such
	*@return 0 if everything ok, 1 otherwise
	*/
	int employSomeone(Employee* bossW);
	/**
	*@brief menu used by the admin with the highest job("Boss") to change other admins information
	*@param bossW - admin information so he cant change is own salary and such
	*@return 0 if everything ok, 1 otherwise
	*/
	int editEmployee(Employee* bossW);
	/**
	*@brief searches the list of restaurants by type and sorts them by the amount of sales and the amount of  products of that type. Also sorts the products showing the products with the disered type first and sorted by times sold
	*@param type - the type of disered cuisine
	*@return the sorted vector of restaurants
	*/
	vector<Restaurant*> searchByCuisine(string type);

	/**
	*@brief updated version of the addDelivery that updates the restaurant,clients and employees and sorts them
	*@param d - delivery to be added
	*/
	void insertDelivery(Delivery* d);
	/**
	*@brief updates all the files of the base by calling the updateFile functions
	*/
	void baseUpdater() const{
		updateClientFile();
		updateRestaurantFile();
		updateEmployeeFile();
		updateDeliveryFile();
		updateTechFile();
	}
	/**
	*@brief menu used by the client to order food
	*@param client - the client making the order
	*@return 0 if everything ok, 1 otherwise
	*/
	int Order(Client *client);
	/**
	*@brief menu used to search the restaurants
	*@param c - client doing the searching
	*@return 0 if everything ok, 1 otherwise
	*/
	int restaurantSearcher(Client *c);
	/**
	*@brief menu used by the client to change his own information
	*@param index - postion of the client in the vector so it is easier to change
	*@return 0 if everything ok, 1 otherwise
	*/
	int clientEditer(Client *client);
	/**
	*@brief menu used by the client to access everything he can
	*@param c - client the logged in
	*@return 0 if everything ok, 1 otherwise
	*/
	int clientInterfaceMenu(Client* c);
	/**
	*@brief menu used by the admin with the highest job("Boss") to change other admins information, remove or add new (calls the other menus)
	*@param bossW - admin information so he cant change is own salary and such
	*@return 0 if everything ok, 1 otherwise
	*/
	int employeeMenu(Employee *bossW);




	int maintenanceMenu();

	/**
	*@brief menu used by the admin with the job "Restaurant Manager" or "Boss" to change products
	*@param resEdit - restaurant that the products are going to be edited
	*@return 0 if everything ok, 1 otherwise
	*/
	int editProduct(string resEdit);
	/**
	*@brief menu used by the admin with the job "Restaurant Manager" or "Boss" to edit a restaurant
	*@return 0 if everything ok, 1 otherwise
	*/
	int resEdit();
	/**
	*@brief menu used by the admin with the job "Restaurant Manager" or "Boss" to add a restaurant
	*@return 0 if everything ok, 1 otherwise
	*/
	int resAdder();
	/**
	*@brief menu used by the admin with the job "Client Manager" or "Boss" to see or send to the blacklist clients
	*@return 0 if everything ok, 1 otherwise
	*/
	int clientMenu();
	/**
	*@brief menu used by the admin with the job "Restaurant Manager" or "Boss" to access the other menus related to restaurants
	*@return 0 if everything ok, 1 otherwise
	*/
	int restaurantMenu();/**
	*@brief menu used to see the deliveries
	*@return 0 if everything ok, 1 otherwise
	*/
	int deliveriesMenu();
	/**
	*@brief menu used by the deliverers
	*@param e - employee using the menu
	*@return 0 if everything ok, 1 otherwise
	*/
	int deliverersMenu(Employee *e);
	/**
	*@brief menu used by the admins
	*@param e - employee using the menu
	*@return 0 if everything ok, 1 otherwise
	*/
	int mainMenuAdmins(Employee *e);
	/**
	*@brief menu used by the admins to see the profit made 
	*@return 0 if everything ok, 1 otherwise
	*/
	int profitMenu();


	int newEmployee();


	void setVehicleTree() {
		for (auto i : vehicles) {
			treeVe.insert(*i);
		}
	}
	BST<Vehicle> getVehicleTree() const {
		return treeVe;
	}

	void updateVehicleTree(int prevKm, int prevN, Vehicle v1) {

		Vehicle v = treeVe.find(Vehicle(prevKm, prevN));
		treeVe.remove(v);
		treeVe.insert(v1);
	}

	Vehicle leastUsedVehicle() {
		return treeVe.findMin();
	}
	Vehicle mostUsedVehicle() {
		return treeVe.findMax();
	}



	void increaseKm(Client* c, Restaurant* r, Vehicle* v) {
		int km = randomKilGenerator(c->getMunicipality(), r->getAddress()->getMunicipality());
		int nD = v->getNDeliveries();
		v->addKms(km);
		v->addDelivery();
		updateVehicleTree(km, nD, *v);
	}

	void printVehiclesPerLessUsage() {
		BSTItrIn<Vehicle> it(treeVe);
		while (!it.isAtEnd()) {
			cout << it.retrieve().printOrg() << endl;
			it.advance();
		}
	}
	
	void printVehiclesPerMostUsage() {
		BSTItrIn<Vehicle> it(treeVe);
		stack<Vehicle>v;
		while (!it.isAtEnd()) {
			v.push(it.retrieve());
			it.advance();
		}
		while (!v.empty()) {
			cout << v.top().printOrg() << endl;
			v.pop();
		}
	}


	bool checkNeighbouring(string m) {
		for (auto i : neighbouring) {
			if (compare_str(m, i))
				return true;
		}
		return false;
	}

};


class Company {
	vector<Base*> bases;/**<vector of the bases*/
	string BaseFile;/**<name of the file with the bases information*/
public:
	Company() = default;
	Company(string filename);
	/**
	*@brief set method
	*/
	void setBases(vector<Base*> b) { this->bases = b; }
	/**
	*@brief get method
	*/
	vector<Base*> getBases() { return bases; }
	/**
	*@brief set method
	*/
	void setBaseFile(string f) { this->BaseFile = f; }
	/**
	*@brief get method
	*/
	string getBaseFile() { return BaseFile; }
	/**
	*@brief calculates the total profit of the company
	*/
	float profit(Date* beg, Date* end) {
		float result = 0;
		for (auto a : bases) result += a->moneyMade(beg, end);
		return result;
	}
	/**
	*@brief calls each base updater
	*/
	void basesUpdater()const {
		for (auto a : bases) {
			a->baseUpdater();
		}
	}
	/**
	*@brief updates the company file
	*/
	void updateCompanyfile()const;
	/**
	*@brief main menu that calls the other menus
	*@return 0 always
	*/
	int mainMenu();
	/**
	*@brief sign up menu for clients
	*@param client being created
	*@return 1 if client not created, otherwise 0
	*/
	int newClient(Client& newC);

	Base* check_Municipality(string s) {

		for (auto i : bases) {
			if (i->checkNeighbouring(s) || compare_str(i->getMunicipality(), s))
				return i;
		}
		throw MunicipalityNotCovered(s);
	}

};



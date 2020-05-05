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
#include "Extra_functions.h"
#include "Clients.h"



class Delivery;

class Vehicle;
using namespace std;

class Vehicle {
	string brand;/**<vehicle's brand*/
	string model;/**<vehicle's model*/
	Date* aquisition;/**<vehicle's date of aquisition*/

	int kms;
	int ndeliveries;
	bool available;
	pair<Time,Date> lastmain;


public:
	/**
	*@brief constructor
	*/
	Vehicle() :brand("Golf Cart"), model("electric buggy"), aquisition(new Date(currentTimeNDate().second)),kms(0),ndeliveries(0),available(true) {};
	/**
	*@brief constructor
	*/
	Vehicle(string b, string m, Date* d) {
		this->brand = b;
		this->model = m;
		this->aquisition = d;
		this->kms = 0;
		this->ndeliveries = 0;
		this->available = true;
	}
	/**
	*@brief constructor
	*/
	Vehicle(string v) {
		vector<string>parts = decompose(v, ',');
		brand = parts.at(0);
		model = parts.at(1);
		aquisition = new Date(parts.at(2));
		kms = mstoi(parts.at(3));
		ndeliveries = stoi(parts.at(4));
		lastmain = readDateNTime(parts.at(5));

	}

	/**
	*@brief constructor
	*/
	Vehicle(int km, int nD) :kms(km), ndeliveries(nD) {};

	/**
	*@brief destructor
	*/
	~Vehicle() = default;
	/**
	*@brief set method
	*/
	void setBrand(string b) { this->brand = b; }
	/**
	*@brief get method
	*/
	string getBrand() const { return brand; }
	/**
	*@brief set method
	*/
	void setModel(string m) { this->model = m; }
	/**
	*@brief get method
	*/
	string getModel() const { return model; }
	/**
	*@brief set method
	*/
	void setAquisition(Date* d) { this->aquisition = d; }
	/**
	*@brief get method
	*/
	Date* getAquisition() const { return aquisition; }


	void setKms(int kms) { this->kms = kms; }
	int getKms() { return kms; }
	void addKms(int n) { kms += n; }

	void setNDeliveries(int n) { this->ndeliveries = n; }
	int getNDeliveries() { return ndeliveries; }
	void addDelivery() { ndeliveries++; }

	void setAvailable(bool i) { this->available = i; }
	bool getAvailable() { return available; }

	void setLastMain(pair<Time,Date> d) { this->lastmain = d; }
	pair<Time,Date> getLastMain() const { return lastmain; }

	/**
	*@brief Operator <<
	*@param a - vehicle being streamed
	*@return a ostream with the vehicle
	*/

	friend ostream& operator<<(ostream& out, Vehicle& v) {
		out << v.getBrand() << ", " << v.getModel() << ", " << *v.getAquisition() << ", " << v.getKms() << ", " << v.getNDeliveries() << ", " << v.getLastMain().first.hour << ":" << v.getLastMain().first.min << "-" << v.getLastMain().second;
		return out;
	}

	/**
	*@brief returns string with vehicle information in a neat way
	*@return string with vehicle
	*/
	string printOrg() const{
		stringstream s;
		s << "Brand and Model: " << brand << " " << model << endl;
		s << "Date of Aquisition: " << *aquisition << endl;
		s << "Last maintenance: " << lastmain.first.hour << ":" << lastmain.first.min << "-" << lastmain.second << endl;
		s << "Kilometers and deliveries made: " << kms << " km / " << ndeliveries << " deli" << endl;
		return s.str();

	}


	bool operator <(Vehicle v) const{
		if (ndeliveries < v.getNDeliveries())return true;
		if (ndeliveries > v.getNDeliveries())return false;
		return kms < v.getKms();
	}
};

class Employee {

	string name; /**<name of the employee*/
	int nif;/**<employee's nif*/
	Date* birthday;/**<employee's birthday*/
	string password;/**<employee's password*/
	float salary;/**<employee's salary*/
	Vehicle* vehicle;/**<employee's vehicle*/
	bool working;/**<bool saying if the employee is still working for the base or not*/
public:
	/**
	*@brief constructor
	*/
	Employee() :name(""), nif(0), birthday(new Date()),salary(0),password(""),vehicle(new Vehicle()),working(true) {};
	/**
	*@brief constructor
	*/
	Employee(string n, string p, int nif, Date* b, float s, Vehicle* v) : name(n), password(p), nif(nif), birthday(b), salary(s), vehicle(v), working(true) {};
	/**
	*@brief constructor
	*/
	Employee(string n, string p, int nif, Date* b, float s, Vehicle* v, bool w) : name(n), password(p), nif(nif), birthday(b), salary(s), vehicle(v), working(w) {};
	/**
	*@brief destructor
	*/
	~Employee() = default;
	/**
	*@brief set method
	*/
	void setName(string n) { this->name = n; };
	/**
	*@brief get method
	*/
	string getName() const { 
		string name2 = name;
		//accentPlace(name2);
		return name2; 
	}
	/**
	*@brief set method
	*/
	void setNif(int nif) { this->nif = nif; };
	/**
	*@brief get method
	*/
	int getNif() const { return nif; }
	/**
	*@brief virtual set method to be used by derived classes
	*/
	virtual void setAJob(string s){}
	/**
	*@brief set method
	*/
	void setDate(Date* d) { this->birthday = d; }
	/**
	*@brief get method
	*/
	Date* getDate() const { return birthday; }
	/**
	*@brief set method
	*/
	void setSalary(float s) { this->salary = s; }
	/**
	*@brief get method
	*/
	float getSalary() const{ return salary; }
	/**
	*@brief set method
	*/
	void setWorking(bool w) { this->working = w; }
	/**
	*@brief get method
	*/
	bool getWorking()const { return working; }
	/**
	*@brief set method
	*/
	void setPassword(string p) { this->password = p; }
	/**
	*@brief get method
	*/
	string getPassword()const { return password; }
	/**
	*@brief set method
	*/
	void setVehicle(Vehicle* v) { this->vehicle = v; }
	/**
	*@brief get method
	*/
	Vehicle* getVehicle() const{ return vehicle; }
	/**
	*@brief virtual function to be used by the deliverer to add a delivery
	*@param d - delivery to be added
	*/
	virtual void addDelivery(Delivery* d) {};
	/**
	*@brief virtual function to be used by the deliverer to calculate the modey made by that deliverer
	*@param beg - begging date
	*@param end - end date
	*@return 0 because it is suposed to be used by the deliverers
	*/
	virtual float moneyMade(Date* beg, Date* end)const { return 0; }
	/**
	*@brief virtual function to be used by the deliverer to get the deliveries made
	*@return d - empty deliveries vector
	*/
	virtual vector<Delivery*> getHistory() const{ 
		vector<Delivery*> d;
		return d; 
	}
	/**
	*@brief virtual get method to be used by derived classes
	*/
	virtual string getAJob() const{
		return "";
	}
	/**
	*@brief virtual get method to be used by derived classes
	*/
	virtual float getMedRating() { return 0.0; }
	/**
	*@brief virtual update method to be used by derived classes
	*/
	virtual void updateRating(){ return; }

	virtual bool isDeliverer() const{
		return false;
	};


	virtual string printSimplified() { return""; }



	/**
	*@brief Operator ==
	*@param e - employee being compared to
	*@return true if the employee is the same
	*/
	bool operator==(Employee* e) { 
		if (nif == e->getNif()) return true;
		return false;
	}
	/**
	*@brief Operator <
	*@param e - employee being compared to
	*@return true if the employee is considered  smaller than the other else false (admin >deliverer, after that is by salary)
	*/
	bool operator<(Employee e) {
		const bool d1 = isDeliverer();
		const bool d2 = e.isDeliverer();
		const float g1 = salary;
		const float g2 = e.getSalary();
		const string j1 = getAJob();
		if (d1 && !d2) return true;
		if (!d1 && d2) return false;
		if (d1 && d2 && (g1 < g2)) return true;
		if (d1 && d2 && (g1 > g2)) return false;
		if (!d1 && !d2) if (compare_str(j1, "Boss")) return false;
		if (!d1 && !d2 && (g1 < g2)) return true;
		return false;
	}
	/**
	*@brief Operator >
	*@param e - employee being compared to
	*@return true if the employee is considered bigger than the other else false (admin >deliverer, after that is by salary)
	*/
	bool operator>(Employee e) {
		const bool d1 = isDeliverer();
		const bool d2 = e.isDeliverer();
		const float g1 = salary;
		const float g2 = e.getSalary();
		const string j1 = e.getAJob();
		if (!d1 && d2) return true;
		if (d1 && !d2) return false;
		if (d1 && d2 && (g1 > g2)) return true;
		if (d1 && d2 && (g1 < g2)) return false;
		if (!d1 && !d2) if (compare_str(j1, "Boss")) return false;
		if (!d1 && !d2 && (g1 > g2)) return true;
		return false;
	}






};

class Admin : public Employee {

	string job;/**<specified the admins position*/

public:
	/**
	*@brief constructor
	*/
	Admin() :Employee(), job("") {};
	/**
	*@brief constructor
	*/
	Admin(string n, string p,int nif, Date* b, float s, string job, Vehicle* v) : Employee(n, p,nif, b, s, v), job(job) {};
	/**
	*@brief constructor recieving the employee and the job
	*/
	Admin(Employee* p, string j) :Employee(p->getName(), p->getPassword(), p->getNif(), p->getDate(), p->getSalary(), p->getVehicle(), p->getWorking()), job(j) {};
	/**
	*@brief destructor
	*/
	~Admin() = default;
	/**
	*@brief set method
	*/
	void setAJob(string j) { this->job = j; }
	/**
	*@brief get method
	*/
	string getAJob() const{ return job; }
	/**
	*@brief check if is an admin or deliverer
	*@return true because its an admin
	*/
	bool isDeliverer() const{ return false; }
	/**
	*@brief Operator <<
	*@param a - Admin being streamed
	*@return a ostream with the admin
	*/
	friend ostream& operator<<(ostream& out, Admin a) {
		out << "Name: " << a.getName() << endl;
		out << "Nif: " << a.getNif() << endl;
		out << "Born at " << *a.getDate() << endl;
		out << "Salary: " << a.getSalary() << endl;
		out << "Job: " << a.getAJob() << endl;
		out << "Vehicle given by the company:  " << *a.getVehicle() << endl;

		return out;
	}
};

class Deliverer : public Employee {

	vector <Delivery*> history;/**<vector of the deliveries made by the deliverer*/
	float medRating;/**<medium rating of the deliverer*/

public:
	/**
	*@brief constructor
	*/
	Deliverer() :Employee(), medRating(3) {};
	/**
	*@brief constructor
	*/
	Deliverer(string n, string p, int nif, Date* b, float s, Vehicle* v) : Employee(n, p, nif, b, s, v) { this->medRating = 3; };
	/**
	*@brief constructor
	*/
	Deliverer(string n, string p, int nif, Date* b, float s, Vehicle* v,float m) : Employee(n, p, nif, b, s, v),medRating(m) {};
	/**
	*@brief constructor
	*/
	Deliverer(string n, string p,int nif, Date* b, float s, vector<Delivery*> d, Vehicle* v,float m) : Employee(n, p,nif, b, s, v), history(d), medRating(m) {};
	/**
	*@brief constructor
	*/
	Deliverer(string n, string p,int nif, Date* b, float s, vector<Delivery*> d, Vehicle* v) : Employee(n, p,nif, b, s, v), history(d) {
		this->medRating = 3;
		updateRating();
	};
	/**
	*@brief constructor
	*/
	Deliverer(string n, string p, int nif, Date* b, float s, vector<Delivery*> d, Vehicle* v,bool w) : Employee(n, p, nif, b, s, v, w), history(d) {
		this->medRating = 3;
		updateRating();
	};
	/**
	*@brief constructor recieving the employee
	*/
	Deliverer(Employee* p) :Employee(p->getName(), p->getPassword(), p->getNif(), p->getDate(), p->getSalary(), p->getVehicle(),p->getWorking()) { this->medRating = 3; }
	/**
	*@brief constructorrecieving the employee and the history of deliveries
	*/
	Deliverer(Employee* p, vector<Delivery*> d) :Employee(p->getName(), p->getPassword(), p->getNif(), p->getDate(), p->getSalary(), p->getVehicle(), p->getWorking()),history(d),medRating(3) {
		updateRating();
	}
	/**
	*@brief destructor
	*/
	~Deliverer() = default;
	/**
	*@brief set method
	*/
	void setHistory(vector<Delivery*> h) { this->history = h; }
	/**
	*@brief adds a delivery to the vector
	*@param d - delivery to be added
	*/
	void addDelivery(Delivery* d) { history.push_back(d); }
	/**
	*@brief get method
	*/
	vector <Delivery*> getHistory() const { return history; }
	/**
	*@brief check if is an admin or deliverer
	*@return true because its a deliverer
	*/
	bool isDeliverer() const{ return true; }

	/**
	*@brief counts the number of successfull deliveries made by the deliverer
	*@return the number of deliveries that were successfull
	*/
	int succefulDeliveries() const;
	/**
	*@brief set method
	*/
	void setMedRating(float m) { this->medRating = m; }
	/**
	*@brief get method
	*/
	float getMedRating() const{ return medRating; }
	/**
	*@brief calculates the money made by the deliverer between the given dates
	*@param beg - begging date
	*@param end - end date
	*@return the amount of money made between the dates
	*/
	float moneyMade(Date* beg, Date* end) const;

	/**
	*@brief updates the rating of the deliverer based on the deliveries
	*/
	void updateRating();
	/**
	*@brief prints a simplified version of the deliverer's information
	*@return a string with a simplified print of the deliverer
	*/
	string printSimplified() {
		stringstream r;
		r << "Name/Nif: " << getName()<<" - "<<getNif() << endl;
		r << "Salary: " << getSalary()<<" - " << fixed << setprecision(1) << getMedRating() << endl;
		r << "Successful deliveries/Medium Rating: " << succefulDeliveries() << " - " << fixed << setprecision(1) << getMedRating() << endl;
		r << "Drives a " << *getVehicle() << endl;

		return r.str();
	}
	/**
	*@brief Operator <<
	*@param d - being streamed deliverer
	*@return a ostream with the deliverer
	*/
	friend ostream& operator<<(ostream& out, Deliverer d) {
		out << "Name: " << d.getName() << endl;
		out << "Nif: " << d.getNif() << endl;
		out << "Born at " << *d.getDate() << endl;
		out << "Salary: " << d.getSalary() << endl;
		out << "Medium Rating: " << fixed << setprecision(1) << d.getMedRating() << endl;
		out << "Successful deliveries: " << d.succefulDeliveries() << endl;
		out << "Drives a " << *d.getVehicle() << endl;
		return out;
	}
};


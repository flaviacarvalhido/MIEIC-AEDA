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
#include "Address.h"

class Delivery;
using namespace std;

class Client {

	string name;/**< client's name*/
	Address* address;/**< client's address*/
	string municipality;/**< municipality where the client lives*/
	string password;/**< client's password*/
	vector<Delivery*> orders;/**< order history*/
	int nif;/**< client's nif*/
	bool erased;/**< has the account been erased or not*/

public:
	/**
	*@brief default constructor
	*/
	Client():name(""),address(new Address()),municipality(""),password(""),nif(0),erased(false) {};
	/**
	*@brief client class constructor 
	*@param name - client's name
	*@param address - client's address
	*@param nif - client's nif
	*@param erased - has the account been erased or not
	*/
	Client(string n, Address* ad, int nif,bool e):name(n), address(ad),nif(nif),erased(e) {};
	/**
	*@brief client class destructor 
	*/
	~Client() = default;
	/**
	*@brief set method
	*/
	void setName(string n) { this->name = n; }
	/**
	*@brief get method
	*/
	string getName() const { return name; }
	/**
	*@brief set method
	*/
	void setAddress(Address* a) { this->address = a; }
	/**
	*@brief set method
	*/
	void setAddress(string a) {
		Address*m= new Address(a);
		this->address = m;
	}
	/**
	*@brief get method
	*/
	Address* getAddress() const { return address; }
	/**
	*@brief set method
	*/
	void setMunicipality(Address* a) {
		this->municipality = a->getMunicipality();
	}
	/**
	*@brief set method
	*/
	void setMunicipality(string m) {
		this->municipality = m;
	}
	/**
	*@brief set method
	*/
	void setErased(bool e) { this->erased = e; }
	/**
	*@brief get method
	*/
	bool getErased()const { return erased; }
	/**
	*@brief get method
	*/
	string getMunicipality() const { return municipality; }
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
	void setOrders(vector<Delivery*> d) { this-> orders = d; }
	/**
	*@brief get method
	*/
	vector<Delivery*> getOrders() const { return orders;}
	/**
	*@brief adds an order to the client
	*@param d - order being addded
	*/
	void addOrder(Delivery* d) {
		orders.push_back(d);
	}

	float totalSpent();
	/**
	*@brief set method
	*/
	void setNif(int n) { this->nif = n; };
	/**
	*@brief get method
	*/
	int getNif() const { return nif; }
	
	/**
	*@brief Operator == 
	*@param c - client being compared to
	*@return true if the clients are the same else false
	*/
	bool operator==(Client c) const {
		if (nif == c.getNif()) return true;
		return false;
	}
	/**
	*@brief Operator <
	*@param c - client being compared to
	*@return true if the client is considered smaller than the other else false
	*/
	bool operator<(Client c)const {
		if (orders.size() < c.getOrders().size()) return true;
		if (orders.size() == c.getOrders().size() && nif < c.getNif()) return true;
		return false;
	}
	/**
	*@brief Operator >
	*@param c - client being compared to
	*@return true if the client is considered bigger than the other else false
	*/
	bool operator>(Client c)const {
		if (orders.size() > c.getOrders().size()) return true;
		if (orders.size() == c.getOrders().size() && nif > c.getNif()) return true;
		return false;
	}
	/**
	*@brief Operator <<
	*@param c - being streamed client
	*@return a ostrem with the printed client
	*/
	friend ostream& operator<<(ostream& out, Client& c) {
		string name = c.getName();
		//accentPlace(name);
		out << "Name: " << name<< endl;
		out << "Nif: " << c.getNif() << endl;
		out << "Address: " << c.getAddress() << endl;
		out << "Number of orders: " << c.getOrders().size() << endl;
		out << "Total money spent: " << c.totalSpent() << endl;
		return out;
	}
	/**
	*@brief Prints the orders made by the client
	*/
	void orderViewer();

};

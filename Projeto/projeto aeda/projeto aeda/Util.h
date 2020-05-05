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
#include "Restaurants.h"
//#include "Employees.h"
//#include "Clients.h"
#include "Address.h"

using namespace std;
class Employee;
class Deliverer;
class Client;


class Delivery {

	int id; /**<id of the delivery*/
	Date* date;/**<date of the delivery*/
	Time time;/**<time of the delivery*/
	Deliverer* deliverer;/**<deliverer who realised the delivery*/
	Client* client;/**<client who placed the order*/
	Restaurant* restaurant;/**<restaurant that the delivery was made from*/
	vector <pair<Product*,int>> products;/**<list of products and amout*/
	float price;/**<final price*/
	bool ok;/**<bool checking if the delivery went well*/
	bool rated;/**<bool checking if the delivery was rated*/
	float rating;/**<dellivery's rating in case of it being rated*/
	string occurrence;/**<if the delivery didnt go well it states the reason, otherwise it can contain a comment if the client so desires*/

public:
	/**
	*@brief constructor
	*/
	Delivery(); 
	/**
	*@brief constructor
	*/
	Delivery(int id, Date* d, Time t, Deliverer* l, Client* c, Restaurant* r, vector <pair<Product*,int>> p, float price, bool ok, bool rated, float rating,string oc) :id(id), date(d), time(t), deliverer(l), client(c), restaurant(r), products(p), price(price),rated(rated),rating(rating),ok(ok), occurrence(oc) {};
	/**
	*@brief destructor
	*/
	~Delivery() = default;
	/**
	*@brief set method
	*/
	void setId(int id) { this->id = id; };
	/**
	*@brief get method
	*/
	int getId() const { return id; }
	/**
	*@brief set method
	*/
	void setDate(Date* d) { this->date = d; }
	/**
	*@brief get method
	*/
	Date* getDate() const { return date; }
	/**
	*@brief set method
	*/
	void setTime(Time t) { this->time = t; }
	/**
	*@brief set method
	*/
	void setTime(string t) {
		vector<string> parts = decompose(t, ':');
		this->time.hour = stoi(parts[0]);
		this->time.min = stoi(parts[1]);
	}
	Time getTime() const { return time; }
	/**
	*@brief set method
	*/
	void setDeliverer(Deliverer* d) { this->deliverer = d; }
	/**
	*@brief get method
	*/
	Deliverer* getDeliverer() const { return deliverer; }
	/**
	*@brief set method
	*/
	void setClient(Client* c) { this->client = c; }
	/**
	*@brief get method
	*/
	Client* getClient() const { return client; }
	/**
	*@brief set method
	*/
	void setRestaurant(Restaurant* r) { this->restaurant = r; }
	/**
	*@brief get method
	*/
	Restaurant* getRestaurant() const { return restaurant; }
	/**
	*@brief set method
	*/
	void setProducts(vector <pair<Product*,int>> p) { this->products = p; }  
	/**
	*@brief adds the products and quantity to the delivery
	*@param p - pair of product and number of that product
	*/
	void addProduct(pair<Product*,int> p);
	/**
	*@brief get method
	*/
	vector <pair<Product*,int>> getProducts() const { return products; }
	
	/**
	*@brief set method
	*/
	void setPrice(float p) { this->price = p; }
	/**
	*@brief get method
	*/
	float getPrice() const { return price; }
	/**
	*@brief calculates the price of the delivery
	*/
	void calculatePrice();
	/**
	*@brief set method
	*/
	void setRated(bool r) { this->rated = r; }
	/**
	*@brief get method
	*/
	bool getRated()const { return rated; }
	/**
	*@brief set method
	*/
	void setRating(float r) { this->rating = r; }
	/**
	*@brief get method
	*/
	float getRating()const { return rating; }
	/**
	*@brief set method
	*/
	void setOk(bool o) { this->ok = o; }
	/**
	*@brief get method
	*/
	bool getOk() const { return ok; }
	/**
	*@brief set method
	*/
	void setOccurrence(string o) { this->occurrence = o; };
	/**
	*@brief get method
	*/
	string getOccurrence() const { return occurrence; }


	/**
	*@brief Operator ==
	*@param d - delivery being compared to
	*@return true if the delivery is the same otherwise false
	*/
	bool operator==(Delivery& d) {
		if (id == d.getId())return true;
		return false;
	}

	/**
	*@brief Operator <<
	*@param s - Admin being streamed
	*@return a ostream with the delivery
	*/
	friend ostream& operator<<(ostream& out, Delivery& d); 


	

};







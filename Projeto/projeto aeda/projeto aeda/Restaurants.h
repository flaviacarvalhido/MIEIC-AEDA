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
#include "Address.h"
#include <set>


class Address;

using namespace std;

class Product{
	string name;/**<product's name */
	string type;/**<product's type of cuisine*/
	float price;/**<product's price */

public:
	/**
	*@brief constructor
	*/
	Product() {
		this-> price = 0;
	};
	/**
	*@brief constructor
	*/
	Product(string name, string type, float price) {
		this->name = name;
		this->type = type;
		this->price = price;
	}
	/**
	*@brief destructor
	*/
	~Product() = default;
	
	
	/**
	*@brief set method
	*/
	void setName(string n) { this->name = n; }
	/**
	*@brief get method
	*/
	string getName() { return name; }
	/**
	*@brief set method
	*/
	void setType(string t) { this->type = t; }
	/**
	*@brief get method
	*/
	string getType() { return type; }
	/**
	*@brief set method
	*/
	void setPrice(float p) { this->price = p; }
	/**
	*@brief get method
	*/
	float getPrice() { return price; }
	/**
	*@brief Operator ==
	*@param p - product being compared to
	*@return true if the products are the same
	*/
	bool operator==(Product &p) {
		if ((name == p.getName()) && (type == p.getType()) && (price=p.getPrice())) return true;
		return false;
	}
	/**
	*@brief Operator <<
	*@param rpoduct - product being streamed
	*@return a ostream with the product
	*/
	friend ostream& operator<<(ostream& out, Product& product) {
		string name = product.getName();
		accentPlace(name);
		string type = product.getType();
		accentPlace(type);
		out << name << "/" << type << "/" << fixed << setprecision(2) << product.getPrice();
		return out;
	}

};

class NoSuchProduct {
	Product* p;
	

public:
	/**
	*@brief exception constructor
	*/
	NoSuchProduct(Product* p) : p(p) {};
	/**
	*@brief get method
	*/
	Product* getNoSuchProduct() { return p; }
	

};

class NoProductWithSuchName {
	string name;
public:
	/**
	*@brief exception constructor
	*/
	NoProductWithSuchName(string name) :name(name) {};
	/**
	*@brief get method
	*/
	string getNoProductWithSuchName() { return name; }

};
class ThereAreNoProducts {

public:
	/**
	*@brief exception constructor
	*/
	ThereAreNoProducts() = default;
};

class RestaurantHasNoSuchProduct {
	Product* p;
public:
	/**
	*@brief exception constructor
	*/
	RestaurantHasNoSuchProduct(Product* p) :p(p) {};
	/**
	*@brief get method
	*/
	Product* getNonexistentProduct() { return p; }
};
class Restaurant {
	string name;/**<restaurant's name*/
	Address* address;/**<restaurant's address*/
	vector <Product*> products;/**<vector with the list of products*/
	vector <pair<Product*, int>> prodNsales;/**<pair with the products and the number of times they have been ordered so they can be ordered by fsales*/
	vector <pair<string, int>> typeNsales;/**<pair with types and sales of the restaurant so the types can be ordered in the globality of the resataurants*/
	int nSales;/**<restaurant's total number of sales*/
	Time close;/**<restaurant's closing time*/
	bool inactive;/**<bool checking if the restaurant is still covered by the base*/


public:
	/**
	*@brief constructor
	*/
	Restaurant() :name(""), address(new Address()), nSales(0),inactive(false) {
		Time t;
		t.hour = 0;
		t.min = 0;
		this->close = t;
	};
	/**
	*@brief constructor
	*/
	Restaurant(Address* a, string n, Time c) :address(a), name(n), close(c),nSales(0),inactive(false) {};
	/**
	*@brief constructor
	*/
	Restaurant (string a){setAddress(a);}  
	/**
	*@brief destructor
	*/
	~Restaurant() = default;
	/**
	*@brief set method
	*/
	void setName(string n) { this->name = n; }
	/**
	*@brief get method
	*/
	string getName()const {
		string name2 = name;
		//accentPlace(name2);
		return name2;
	}
	/**
	*@brief set method
	*/
	void setProdNsales(vector <pair<Product*, int>> p) { this->prodNsales = p; }
	/**
	*@brief get method
	*/
	vector <pair<Product*, int>> getProdNsales()const { return prodNsales; }
	/**
	*@brief set method
	*/
	void setTypeNsales(vector<pair<string, int>> t) { this->typeNsales=t; }
	/**
	*@brief get method
	*/
	vector<pair<string, int>> getTypeNsales()const { return typeNsales; }
	/**
	*@brief set method
	*/
	void setAddress(Address* a) { this->address = a; }
	/**
	*@brief set method
	*/
	void setAddress(string m) { 
		Address* a=new Address(m);
		this->address=a;
	}
	/**
	*@brief get method
	*/
	Address* getAddress() const { return address; }
	/**
	*@brief set method
	*/
	void setProducts(vector <Product*> p) { this->products = p; }
	/**
	*@brief set method that creates the products, pairs of products and sales and the types and sales 
	*/
	void setProducts(string product) {
		vector<string> raw = decompose(product, ',');
		Product p;
		vector<string> usage;
		vector<Product*>products;
		vector<pair<Product*, int>> ps;
		vector<pair<string, int>> ts;
		set<pair<string, int>> sts;
		//unsigned int it = 0;
		//string prevtype;
		for (auto a : raw) {
			usage = decompose(a, '/');
			p.setName(usage[0]);
			p.setType(usage[1]);
			p.setPrice(stof(usage[2]));
			products.push_back(new Product(p));
			ps.push_back(make_pair(new Product(p), 0));
			sts.insert(make_pair(usage[1], 0));
		}
		for (auto a : sts)ts.push_back(a);
		this->typeNsales = ts;
		this->products = products;
		this->prodNsales = ps;
	}
	/**
	*@brief adds a product to the vectors and checks if the type of the products is already included in the types vector
	*@param p - product being added
	*/
	void addProducts(Product* p) { 
		products.push_back(p); 
		prodNsales.push_back(make_pair(p, 0));
		bool type = false;
		for (auto a : typeNsales) {
			if (compare_str(p->getType(), a.first)) {
				type=true;
				break;
			}
		}
		if (!type)typeNsales.push_back(make_pair(p->getType(), 0));
	}
	/**
	*@brief get method
	*/
	vector <Product*> getProducts() const { return products; }
	/**
	*@brief sorts the products vector acording to the sales vector
	*/
	void sortProd() {
		vector<Product*>p;
		for (auto a : prodNsales) p.push_back(a.first);
		this->products = p;
	}
	/**
	*@brief sets the desired product's price negative (our way of removing it without messing up the deliveries and the employees)
	*@param name - name of the product being "removed"
	*/
	void removeProduct(string name) {
		sortProd();
		float price;
		for (unsigned int i = 0; i < products.size(); i++) {
			if (compare_str(products[i]->getName(), name)) {
				price=products[i]->getPrice();
				products[i]->setPrice(-price);
				prodNsales[i].first->setPrice(-price);
			}
		}
		
	}
	/**
	*@brief sets the desired product's price negative (our way of removing it without messing up the deliveries and the employees)
	*@param it - position of the product being "removed" in the vector
	*/
	void removeProduct(int it) {
		sortProd();
		float price;
		price = products[it]->getPrice();
		products[it]->setPrice(-price);
		prodNsales[it].first->setPrice(-price);
	}
	/**
	*@brief set method
	*/
	void setClose(Time t) {this->close = t;}
	/**
	*@brief get method
	*/
	Time getClose()const { return close;}
	/**
	*@brief previous removing method that in not used because it messed up with the other classes that have products in it (threw an exception if the product wasn't found)
	*@param p - product being "removed" in the vector
	*/
	void NotForSale(Product* p) {
		sortProd();
		for (unsigned int i = 0; i < products.size(); i++) {
			if (products[i] == p) {
				products.erase(products.begin() + i);
				prodNsales.erase(prodNsales.begin() + i);
				return;
			}
		}
		throw NoSuchProduct(p);
	}
	/**
	*@brief set method
	*/
	void setNSales(int n) { this->nSales = n; }
	/**
	*@brief increments the sales by 1
	*/
	void incrementSales() { this->nSales++; }
	/**
	*@brief get method
	*/
	int getNSales() const{ return nSales; }
	/**
	*@brief set method
	*/
	void setInactive(bool b) { this->inactive = b; }
	/**
	*@brief get method
	*/
	bool getInactive()const { return inactive; }
	bool operator==(Restaurant r) {
		if (name == r.getName()) return true;
		return false;
	}

	Product* findProduct(string name) {
		for (auto a : products) {
			if (a->getName() == name)return a;
		}
		throw NoProductWithSuchName(name);
	}
	/**
	*@brief checks if the restaurant has a certain type of product
	*@param type - the desired type
	*@return true if the restaurant has the disered type otherwise false
	*/
	bool hasType(string type) {
		for (auto a : products)return true;
		return false;

	}
	/**
	*@brief counts the number of products that a restaurant sells of a certain type 
	*@param type - the desired type
	*@return number of the number products of that type
	*/
	int nProdType(string type) const{
		int result = 0;
		for (auto a : products) if (compare_str(a->getType(), type)) result++;
		return result;
	}
	/**
	*@brief ccalculates the medium price of the products in a restaurant
	*@return medium price 
	*/
	float medPrice() {
		float total = 0;
		for (auto a : products) total += a->getPrice();
		return total / products.size();
	}
	/**
	*@brief checks the type of cuisine the restaurant has the most of
	*@return the name of of that type
	*/
	string predominantCuisine() {
		string type;
		int last = 0;
		for (unsigned int i = 0; i < typeNsales.size(); i++) {
			
			if (last < nProdType(typeNsales[i].first)) {
				type = typeNsales[i].first;
				last = typeNsales[i].second;
			}
		}
		return type;
	}
	/**
	*@brief check the most sold type in a restaurant
	*@return the name of the most sold type of cuisine in that restaurant
	*/
	string mostSoldCuisine() {
		pair<string, int> p;
		for (unsigned int i = 0; i < typeNsales.size(); i++) {
			if (i == 0) p = typeNsales[i];
			else if (p.second < typeNsales[i].second) p = typeNsales[i];
		}
		return p.first;
	}
	/**
	*@brief prints the products of the restaurant and checks if they are available or not
	*@return string with the products
	*/
	string printProductsMenu() {
		stringstream result;
		for (unsigned int i = 0; i < products.size(); i++) {
			string name = products[i]->getName();
			string type = products[i]->getType();
			//accentPlace(name);
			//accentPlace(type);
			result << name << "/" << type << "/";
			if (products[i]->getPrice() < 0)result << "UNAVAILABLE";
			else result<< fixed << setprecision(2) << products[i]->getPrice()<<", ";
			if (i % 3==0)result << endl;
		}
		return result.str();
	}
	/**
	*@brief prints the products of the restaurant
	*@return string with the products
	*/
	string printProducts() {
		stringstream result;
		for (unsigned int i = 0; i < products.size();i++) {
			if (i != products.size() - 1) result << *products.at(i) << ", ";
			else result << *products.at(i);
		}
		return result.str();
	}
	/**
	*@brief Operator <
	*@param r - restaurant being compared to
	*@return true if the restaurant is considered  smaller than the other else false (number of sales)
	*/
	bool operator<(Restaurant r) {
		const int r1s = nSales;
		const int r2s = r.getNSales();
		if (r1s < r2s) return true;
		//if ((r1.getNSales() == r2.getNSales()) && (r1.getProducts().size() < r2.getProducts().size())) return true;
		return false;

	}
	/**
	*@brief Operator <
	*@param r - restaurant being compared to
	*@return true if the restaurant is considered bigger than the other else false (number of sales)
	*/
	bool operator>(Restaurant r) {
		const int r1s = nSales;
		const int r2s = r.getNSales();
		if (r1s > r2s) return true;
		//if ((r1.getNSales() == r2.getNSales()) && (r1.getProducts().size() < r2.getProducts().size())) return true;
		return false;

	}
	/**
	*@brief prints the products of the restaurant in a simples way
	*@return string with the products in a simplified view
	*/
	string printSimplified() {
		stringstream out;
		string name = getName();
		//accentPlace(name);
		string pred = predominantCuisine();
		//accentPlace(pred);
		out << "Name: " << name << endl;
		out << "Predominant cuisine: " << pred << endl;
		out << "Average price/Total sales in the app: " << medPrice() << "€/"<<getNSales() << endl;
		return out.str();
	}
	/**
	*@brief Operator <<
	*@param r - Restaurant being streamed
	*@return a ostream with the restaurant
	*/
	friend ostream& operator<<(ostream& out, Restaurant& r) {
		string name = r.getName();
		//accentPlace(name);
		string pred = r.predominantCuisine();
		//accentPlace(pred);
		out << "Name: " << name << endl;
		out << "Address: " << *r.getAddress() << endl;
		out << "Products: "<<r.printProductsMenu() << endl; //use only top products?
		out << "Predominant cuisine: " <<pred<< endl;
		out << "Average price: " << r.medPrice() << "€" << endl;
		out << "Total sales in the app: " << r.getNSales() << endl;
		return out;
	}

};


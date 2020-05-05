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
#include "Date.h"
#include "Util.h"
#include "Employees.h"
#include "Clients.h"
using namespace std;


class imp {
public:
	/**
*@brief sorting condition to sort employees by importance
*@param e1 - client being compared
*@param e2 - client being compared
*@return true if e1 is considered a more important than e2
*/
	bool operator()(const Employee* e1,const Employee* e2) {
		Employee e3 = *e1;
		Employee e4 = *e2;
		if (e3 > e4)return true;
		return false;
	}
}importance;


class most {
public:
	/**
*@brief sorting condition to sort the restaurants by sales
*@param r1 - restaurant being compared
*@param r2 - restaurant being compared
*@return true if r1 has more sales than r2
*/
	bool operator()(const Restaurant* r1, const  Restaurant* r2) {
		const int r1s = r1->getNSales();
		const int r2s = r2->getNSales();
		if (r1s > r2s) return true;
		//if ((r1.getNSales() == r2.getNSales()) && (r1.getProducts().size() < r2.getProducts().size())) return true;
		return false;
	}

}mostVisited;

class sold {
public:
	/**
*@brief sorting condition to sort the products by sales
*@param p1 - pair of product and sales
*@param p2 - pair of product and sales
*@return true if p1 has sod more than p2, in case of a tie the biggest price wins
*/
	bool operator()(const pair<Product*,int> p1, const pair<Product*, int>  p2) {
		int s1 = p1.second;
		int s2 = p2.second;
		float pr1 = p1.first->getPrice();
		float pr2 = p2.first->getPrice();
		if (s1 > s2) return true;
		if ((s1 == s2) && (pr1 > pr2)) return true;
		return false;
	}
}mostSold;


class bestClient {
public:
	/**
*@brief sorting condition to sort the clients by best client (operator> can be redifined)
*@param c1 - client being compared
*@param c2 - client being compared
*@return true if c1 is considered a better client than p2
*/
	bool operator() (const Client* c1, const Client* c2) {
		Client c3 = *c1;
		Client c4 = *c2;
		if (c3 > c4)return true;
		return false;
	}
}bC;


class pr {
public:
	/**
*@brief sorting condition to sort the typeNsales vector by number of sales
*@param p1 - pair of type and quantity
*@param p2 - pair of type and quantity
*@return true if p1's quantity is  bigger than p2's
*/
	bool operator()(pair<string, int> p1, pair<string, int> p2) {
		if (p1.second > p2.second) return true;
		return false;
	}
}typeNprod;

class low {
public:
/**
*@brief sorting condition to sort the restaurants by med price
*@param r1 - restaurant being compared
*@param r2 - restaurant being compared
*@return true if the medium price of r1 is smaller then r2's
*/
	bool operator()(Restaurant* r1, Restaurant* r2) {
		float m1 = r1->medPrice();
		float m2 = r2->medPrice();
		if (m1 < m2)return true;
		return false;
	}
}lowerPrice;

class high {
public:
	/**
*@brief sorting condition to sort the restaurants by med price
*@param r1 - restaurant being compared
*@param r2 - restaurant being compared
*@return true if the medium price of r1 is bigger then r2's
*/
	bool operator()(Restaurant* r1, Restaurant* r2) {
		float m1 = r1->medPrice();
		float m2 = r2->medPrice();
		if (m1 > m2)return true;
		return false;
	}
}higherPrice;

class Ptype {
public:
/**
*@brief sorting condition to sort the typeNsales vector alphabeticaly
*@param p1 - pair of type and quantity
*@param p2 - pair of type and quantity
*@return true if the string of p1 is "bigger" alphabeticaly
*/
	bool operator()(pair<string, int> p1, pair<string, int> p2) {
		if (p1.first > p2.first) return true;
		return false;
	}
}tname;



/*
 * pizzaria.h
 *
 *  Created on: Oct 21, 2015
 *      Author: RRossetti
 */

#ifndef PIZZERIA_H_
#define PIZZERIA_H_

#include <string>
#include <vector>
#include <set>
#include <iostream>

#include "sequentialSearch.h"
#include "insertionSort.h"

using namespace std;

class Menu {
	int id;
	string name;
	int likes;
	vector<string> ingredients;
public:
	Menu();
	Menu(string n1, vector<string> is1);
	Menu(int id1, string n1, vector<string> is1, int lks1);
	int getId() const;
	void setId(int id1);
	string getName() const;
	void setName(string n1);
	vector<string> getIngredients() const;
	void addLike() { ++likes; }
	int getLikes() const { return likes; }

	void setIngredients(const vector<string> &is1);
	class ExceptionIngredientsRepeated{};

	bool operator != (Menu m1){
	    if(m1.getId()!=id)return true;
	}

    class ExceptionIngredientNotPresent{
        string name;
    public:
        ExceptionIngredientNotPresent(string s1):name(s1){};
        string getIngredient(){return name;}
    };

	void ExceptionThrower(string s1);
};

class Customer {
	int nif;
	string name;
public:
	Customer(int nif1, string n1);
	int getNIF() const;
	string getName() const;
};

class Pizzeria {
	vector<Menu> menus;
	vector<Customer*> customers;
public:
	Pizzeria();
	Pizzeria(vector<Menu> ms1);
	vector<Menu> getMenus() const;
	vector<Customer*> getCustomers() const;
	int addCustomer(Customer* c1);

	vector<Menu> optionsWithinIngredientLimits(int i1, int i2) const;
	vector<Menu> popularityRank() const;
	Customer* chefCustomer();
	Menu& removeIngredient(vector<string> is1, string i1);

	class ExceptionInvalidIngredientLimits{};

	class ExceptionInexistentMenu{};
};

template<class Comparable>
bool isSet(const vector<Comparable>& v1){

    set<Comparable> s1;

    for(unsigned int i=0;i<v1.size();i++){
        s1.insert(v1[i]);
    }

    if(s1.size() == v1.size())return true;
    return false;

}


#endif /* PIZZERIA_H_ */

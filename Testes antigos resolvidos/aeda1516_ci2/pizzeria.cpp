/*
 * pizzeria.cpp
 *
 *  Created on: 25 Oct 2015
 *      Author: RRossetti
 */

#include <algorithm>
#include "pizzeria.h"

/*
 * CLASS MENU
 */

int ID;

Menu::Menu() {
	id = 0;
	name = "";
	likes = 0;
}

Menu::Menu(int id1, string n1, vector<string> is1, int lks1) {
	id = id1;
	name = n1;
	ingredients = is1;
	likes = lks1;
}

int Menu::getId() const { return id; }
void Menu::setId(int id1) { id = id1; }
string Menu::getName() const { return name; }
void Menu::setName(string n1) { name = n1; }
vector<string> Menu::getIngredients() const { return ingredients; }

Menu::Menu(string n1, vector<string> is1) {

    setName(n1);
    likes=0;
    ingredients=is1;
    ID++;
    id=ID;

}

void Menu::setIngredients(const vector<string> &is1) {
    ingredients=is1;
    if(!isSet(ingredients))throw ExceptionIngredientsRepeated();
}


/*
 * CLASS CUSTOMER
 */

Customer::Customer(int nif1, string n1) {
	nif = nif1;
	name = n1;
}

int Customer::getNIF() const {
	return nif;
}

string Customer::getName() const {
	return name;
}


/*
 * CLASS PIZZERIA
 */

Pizzeria::Pizzeria() { }

Pizzeria::Pizzeria(vector<Menu> ms1) {
	menus = ms1;
}

vector<Menu> Pizzeria::getMenus() const { return menus; }

vector<Customer*> Pizzeria::getCustomers() const { return customers; }

int Pizzeria::addCustomer(Customer* c1) {
	customers.push_back(c1);
	return customers.size();
}

vector<Menu> Pizzeria::optionsWithinIngredientLimits(int i1, int i2) const {
    if(i1 < 1 || i2 < 1 || i1>i2){throw ExceptionInvalidIngredientLimits();}

    vector<Menu> res;

    for(unsigned int i=0; i<menus.size();i++){
        if(menus[i].getIngredients().size()>=i1 && menus[i].getIngredients().size()<=i2)
            res.push_back(menus[i]);
    }
    return res;

}

bool popular(Menu m1, Menu m2){
    if(m1.getLikes() > m2.getLikes())return true;
    else if(m1.getLikes() < m2.getLikes())return false;
    else if(m1.getLikes()==m2.getLikes()){
        if(m1.getIngredients().size() > m2.getIngredients().size())return false;
        else if(m1.getIngredients().size() < m2.getIngredients().size())return true;
        else if(m1.getIngredients().size() == m2.getIngredients().size()){
            return m1.getName() < m2.getName();
        }
    }
}

vector<Menu> Pizzeria::popularityRank() const {  //não se pode alterar menus diretamente por ser const!!
    vector<Menu> m=menus;
    sort(m.begin(),m.end(),popular);
    return m;
}

Customer *Pizzeria::chefCustomer() {

    int maxCus=0,maxLikes=0,menunumber=0,likes=0;
    vector<int> likesmenuratio;

    for(unsigned int i=0;i<customers.size();i++){
        menunumber=0;
        likes=0;
        for(unsigned int j=0;j<menus.size();j++){
            if(menus[j].getName()==customers[i]->getName()){
                menunumber++;
                likes+=menus[j].getLikes();
            }
        }
        likesmenuratio.push_back(likes/menunumber);
    }

    maxLikes=likesmenuratio[0];
    maxCus=0;
    for(unsigned int i=1;i<likesmenuratio.size();i++){
        if(maxLikes<likesmenuratio[i]){
            maxLikes=likesmenuratio[i];
            maxCus=i;
        }
    }

    return customers[maxCus];
}

Menu &Pizzeria::removeIngredient(vector<string> is1, string i1) {

    bool foundm=false,foundi=false;
    Menu var;

    for(unsigned int i=0;i<menus.size();i++){
        if(menus[i].getIngredients()==is1){
            foundm=true;
            var=menus[i];
            for(unsigned int j=0;j<menus[i].getIngredients().size();j++){
                if(menus[i].getIngredients()[j]==i1){
                    foundi=true;
                    vector<string> v=menus[i].getIngredients();  //THIS IS HOW YOU ERASE AND UPDATE VECTORS!!! YOU SET A NEW ONE!!
                    v.erase(v.begin()+j);
                    menus[i].setIngredients(v);
                    break;
                }
            }
        }
        if(foundm && foundi)return menus[i];
    }

    if(foundm && !foundi) var.ExceptionThrower(i1);
    if(!foundm)throw ExceptionInexistentMenu();


}

void Menu::ExceptionThrower(string s1){
    throw ExceptionIngredientNotPresent(s1);
}



/*
 * BankOfficer.cpp
 */
#include "BankOfficer.h"

unsigned int idthing=0;

BankOfficer::BankOfficer(): id(0) {}

void BankOfficer::setName(string nm){
	name = nm;
}

string BankOfficer::getName() const{
	return name;
}

vector<Account *> BankOfficer::getAccounts() const {
	return myAccounts;
}

void BankOfficer::addAccount(Account *a) {
	myAccounts.push_back(a);
}

unsigned int BankOfficer::getID() const{
	return id;
}


// ----------------------------------------------------------------------------------------------

// a alterar
BankOfficer::BankOfficer(string name) {
    vector<Account*> my;
    this->name = name;
    idthing=idthing+1;
    this->id = idthing;
    this->myAccounts=my;
}

bool BankOfficer::operator>(const BankOfficer &b1) {
    if(myAccounts.size()> b1.getAccounts().size()){
        return true;
    }else if(myAccounts.size() == b1.getAccounts().size())
    {
        return name > b1.getName();
    }
    return false;
}







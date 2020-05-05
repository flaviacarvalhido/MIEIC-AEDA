/*
 * Account.cpp
 */
#include <iostream>
#include <vector>
#include "Account.h"
using namespace std;

Account::Account(string hold, string codeH, string codeA, double bal): holder(hold), codeHolder(codeH), codeIBAN(codeA), balance(bal) {}

Account::~Account(){ }

string Account::getCodH() const {
	return codeHolder;
}

string Account::getCodIBAN() const {
	return codeIBAN;
}

double Account::getBalance() const {
	return balance;
}

SavingsAccount::SavingsAccount (string hold, string codeH, string codeA, double bal, double pct):
		Account(hold, codeH, codeA, bal), rate(pct/100)
{ }

double SavingsAccount::getCharge() const {
    if((rate*100)>2.0){return 0.8;}
    else{return 0;}
}

double SavingsAccount::getWithdraw() const {
    return balance;
}


CheckingAccount::CheckingAccount(string hold, string codeH, string codeA, double bal,double lim):
			Account(hold, codeH, codeA, bal) {
	limit = lim;
}

double CheckingAccount::getCharge() const {
    if (limit <= 500){return 0.5;}
    else if(limit>500 && limit <= 1000){return 0.25;}
    else if(limit>1000){return 0;}
}

double CheckingAccount::getWithdraw() const {
    if(balance>limit){return limit;}
    return balance;
}


TimeAccount::TimeAccount(string hold, string codeH, string codeA, double bal, double pct):
			SavingsAccount(hold, codeH, codeA, bal, pct) {
	funds_avail = balance*rate;
}

double TimeAccount::getWithdraw() const {
    return funds_avail;
}

/*
template <class T>
unsigned int numberDifferent (const vector<T> & v1){
    vector<T> res = set(v1);
    return res.size();
}
 */



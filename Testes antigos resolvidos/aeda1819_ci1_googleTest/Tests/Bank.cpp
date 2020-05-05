/*
 * Bank.cpp
 */

#include "Bank.h"
#include <algorithm>
#include <string>
#include <vector>

Bank::Bank() {}

void Bank::addAccount(Account *a) {
	accounts.push_back(a);
}

void Bank::addBankOfficer(BankOfficer b){
	bankOfficers.push_back(b);
}

vector<BankOfficer> Bank::getBankOfficers() const {
	return bankOfficers;
}

vector<Account *> Bank::getAccounts() const {
	return accounts;
}


// ----------------------------------------------------------------------------------------------

// a alterar
double Bank::getWithdraw(string cod1) const{
	double result=0;
    for(int i =0;i<accounts.size();i++){
	    if(accounts[i]->getCodH() == cod1){
	        result += accounts[i]->getWithdraw();
	    }
	}
    return result;
}


// a alterar
vector<Account *> Bank::removeBankOfficer(string name){
	vector<Account *> res;
	for(int i=0; i < bankOfficers.size(); i++){
	    if(bankOfficers[i].getName()==name){
	        res=bankOfficers[i].getAccounts();
	        bankOfficers.erase(bankOfficers.begin()+i);
	        break;
	    }
	}
	return res;
}


// a alterar
const BankOfficer & Bank::addAccountToBankOfficer(Account *ac, string name) {

    for(int i=0;i<bankOfficers.size();i++){
        if(bankOfficers[i].getName() == name){
            bankOfficers[i].addAccount(ac);
            return bankOfficers[i];
        }
    }

    throw NoBankOfficerException(name);


}

bool compAcc(Account *a, Account *b){
    if(a->getBalance() < b->getBalance()){
        return true;
    }else if(a->getBalance() == b->getBalance()){
        return a->getCodIBAN() < b->getCodIBAN();
    }
    return false;
}

// a alterar
void Bank::sortAccounts() {
    sort(accounts.begin(),accounts.end(),compAcc);
}


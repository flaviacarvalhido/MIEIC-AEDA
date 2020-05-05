


#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <sstream>
#include <cmath>
#include "Windows.h"
#include "conio.h"

#include "Base.h"
#include "Clients.h"
#include "Employees.h"
#include "Extra_functions.h"
#include "Restaurants.h"
#include "Util.h"

using namespace std;






int main() {
	Company ugh("Bases.txt");
	ugh.mainMenu();		
	
	ugh.basesUpdater();

	//system("pause");
	return 0;
}

int Company::mainMenu() {

	bool stay = true, found = false;
	int option, userNIF, option1;
	string baseOption, login, soption1,pass;


	
	while (stay) {
		system("cls");
		cout << "__________UghEats__________ \n" << endl;
		cout << "Would you like to do?\n1: Login \n2: Sign up \n\n0: Exit program" << endl;
		getline(cin, soption1);


		if ((!isNumber(soption1)) || (soption1 != "0" && soption1 != "1" && soption1 != "2")) {
			cout << "Not a valid option, please try again" << endl;
			continue;
		}

		option1 = stoi(soption1);
		switch (option1) {
		case 0:
			stay = false;
			break;

		case 1:
			cout << endl;
			cout << endl;
			cout << "Please insert your NIF" << endl;
			cout << "Login:";
			login = "";
			getline(cin, login);
			while ((!isNumber(login)) || login.length() != 9) {
				cout << endl;
				cout << endl;
				cout << "Not a valid NIF, please try again" << endl;
				cout << "Login: ";
				getline(cin, login);
			}
			userNIF = stoi(login);
			

			for (unsigned int i = 0; i < bases.size(); i++) {
				for (unsigned int j = 0; j < bases[i]->getClients().size(); j++) {
					//cout << userNIF << "-" << bases[i]->getClients()[j]->getNif() << endl;
					if (userNIF == bases[i]->getClients()[j]->getNif() && !bases[i]->getClients()[j]->getErased()) {
						found = true;
						Client* c = bases.at(i)->getClients()[j];
						pass = "";
						while (pass != c->getPassword()) {
							
							cout << "Password:" << endl;

							pass = read_pass();

							if (compare_str(pass,c->getPassword())) {
								system("CLS");  //clears terminal
								cout << "Welcome back " << c->getName() << "!"<< endl;
								cout << endl;
								cout << endl;
								bases.at(i)->clientInterfaceMenu(c);
								break;
							}
							else {
								cout <<endl<< "Wrong Password! Try again." << endl;
								cout << endl;
								continue;
							}
						}
						

					}
				}
				
				for (unsigned int k = 0; k < bases[i]->getEmployees().size(); k++) {
					if (userNIF == bases[i]->getEmployees()[k]->getNif()) {
						found = true;
						Employee* e = bases.at(i)->getEmployees()[k];

						while (pass != e->getPassword()) {
							cout << "Password:" << endl;

							pass = read_pass();

							if (compare_str(pass,e->getPassword())) {
								system("CLS");  //clears terminal
									
								//wishes happy birthday
								if (*e->getDate() == currentTimeNDate().second) {
									printHB();
									system("pause");
								}

								else {
									cout << "Welcome back " << e->getName() << "!" << endl;
									cout << endl;
									cout << endl;
								}
								if (e->isDeliverer()) {
									bases.at(i)->deliverersMenu(e);
								}
								else {
									bases.at(i)->mainMenuAdmins(e);
								}
								system("pause");
								break;
							}
							else {
								cout <<endl<< "Wrong Password! Try again." << endl;
								cout << endl;
								continue;
							}
						}


					}
				}


				if (found) { break; }
			}
			found = false;
			break;


		case 2:
			Client newC;
			if (newClient(newC) != 0) {
				cout << endl << "Client not added" << endl;
				break;
			}
			//cout << newC.getMunicipality();
			for (unsigned int i = 0; i < bases.size(); i++) {
				bool black = false;
				vector<string> t = bases[i]->getNeighbouring();
				string m = newC.getMunicipality();
				if (compare_str(newC.getMunicipality(), bases[i]->getMunicipality()) || (find(t.begin(),t.end(), m) != t.end())) {
					for (auto a : bases[i]->getBlacklist()) {
						if (*a == newC) {
							cout << "Client in blacklist" << endl;
							black = true;
							break;
						}
					}
					if (black)break;
					bases[i]->addClient(new Client(newC));
					cout << endl << "Successfully registered" << endl;
					system("pause");
					system("CLS");
					bases.at(i)->clientInterfaceMenu(new Client(newC));
					break;
					
				}
			}
			
			break;
		}


	}
	return 0;
}

int Company::newClient(Client& newC) {
	//Client newC;
	string a1, a2, a3, pass, pass2;
	bool sera = false;
	vector<string> va1, va2;
	int anif;
	Base* b;

	while (true) {
		sera = false;
		cout << "Your full name: ";
		getline(cin, a1);
		trim(a1);
		replaceAccent(a1);
		va1 = decompose(a1, ' ');

		for (unsigned int i = 0; i < va1.size(); i++) {

			if (!isWord(va1[i])) {
				cout << "Not a valid input, please do not include any acute accents, circumflex, tilde, punctuation, numbers or cedilla" << endl;
				va1.clear();
				sera = true;
				break;
			}
		}
		if (sera) continue;
		newC.setName(a1);
		break;
	}

	while (true) {
		
			cout << "\nYour address, separated by commas: ";
			//cin.clear();
			//cin.ignore(1000, '\n');
			getline(cin, a2);
			trim(a2);
			va2 = decompose(a2, ',');

			while (va2.size() != 4 || !isAddress(Address(a2))) {
				cout << endl << "Not a valid address, please write it in the following format: Street, Number, Zip code, Municipality" << endl;
				getline(cin, a2);
				trim(a2);
				va2 = decompose(a2, ',');
			}

		try{
			b = check_Municipality(va2[3]);

		}
		catch (MunicipalityNotCovered & e) {

			cout << endl << "MunicipalityNotCovered: UghEats does not reach " << e.getMunicipalityNotCovered() << " and therefore you cannot sign up"<<endl;
			
			Sleep(3000);

			cout << endl << "Returning home..." << endl;

			Sleep(2000);
			return 1;

		}
		newC.setAddress(a2);
		break;
	}

	va2 = decompose(a2, ',');
	newC.setMunicipality(va2[3]);

	while (true) {
		cout << "\nYour NIF: ";
		//cin.clear();
		//cin.ignore(1000, '\n');
		getline(cin, a3);
		trim(a3);
		if (!isNif(a3)) {
			cout << "Not a valid NIF, please try again" << endl;
			continue;
		}
		anif = mstoi(a3);
		newC.setNif(anif);
		break;
	}



	cout << endl << "Input password: " << endl;

	pass = read_pass();

	cout << endl << "Confirm password: " << endl;

	pass2 = read_pass();

	//cout << "here";
	while (!compare_str(pass, pass2)) {
		cout << endl << "Passwords don't match. Please confirm pass again (0 + Enter to cancel)" << endl;


		pass2 = read_pass();
		if (pass2 == "0") {
			cout << endl << "Error setting password" << endl;
			return 1;
		}

	}

	newC.setPassword(pass);

	b->addClient(new Client (newC));

	return 0;
}






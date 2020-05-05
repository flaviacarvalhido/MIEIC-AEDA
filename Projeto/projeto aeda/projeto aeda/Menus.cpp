#include "Base.h"
#include "Extra_functions.h"

#include "Windows.h"
#include "conio.h"

#include <iostream>


using namespace std;


int Base::Order(Client *client) {
	bool found = false, closed=false;
	string rname, idprod, quan, received, comment, var="y";
	Delivery d;

	while (!found) {
		
		closed = false;

		cout << endl;
		cout << "What restaurant would you like to order from? (write the name, please)" << endl;
		getline(cin, rname);


		for (unsigned int i = 0; i < restaurants.size(); i++) {

			if (compare_str(rname, restaurants[i]->getName())) {

				d.setClient(client);
				d.setRestaurant(restaurants[i]);

				if (((restaurants[i]->getClose().hour > currentTimeNDate().first.hour) && (currentTimeNDate().first.hour > 10)) || (restaurants[i]->getClose().hour < 10 && currentTimeNDate().first.hour < restaurants[i]->getClose().hour) || (restaurants[i]->getClose().hour < 10 && currentTimeNDate().first.hour > restaurants[i]->getClose().hour && currentTimeNDate().first.hour > 10) || ((restaurants[i]->getClose().hour == currentTimeNDate().first.hour) && (restaurants[i]->getClose().min > currentTimeNDate().first.min))) {
					cout << endl;
					cout << endl;
					cout << "List of Products Available in said restaurant:" << endl;
					for (unsigned int j = 0; j < restaurants[i]->getProducts().size(); j++) {
						found = true;
						cout << j + 1 << " - " << restaurants[i]->getProducts()[j]->getName() << setw(40- restaurants[i]->getProducts()[j]->getName().length())<<"Type: " << restaurants[i]->getProducts()[j]->getType();
						if (restaurants[i]->getProducts()[j]->getPrice() < 0) {
							cout << setw(20- restaurants[i]->getProducts()[j]->getType().length())<< "UNAVAILABLE" << endl;
						}else {
							cout << setw(20 - restaurants[i]->getProducts()[j]->getType().length()) << "Price: " << fixed << setprecision(2) << restaurants[i]->getProducts()[j]->getPrice() << endl;
						}
					}
					break;
				}
				else {
					cout << restaurants[i]->getName() << " is CLOSED. Try ordering from different restraurant." << endl;
					closed = true;
					break;
				}
				
			}

		}
		if (!found && !closed) {
			cout << "Restaurant not Found: try again" << endl;
			continue;
		}
		
	}

	cout << endl;
	cout << endl;

	while (var == "y") {
		cout << endl;
		cout << "Which Product do you wish to order? (please input one number at a time)" << endl;
		getline(cin, idprod);

		while (stoi(idprod) < 1 || stoi(idprod) > d.getRestaurant()->getProducts().size() || d.getRestaurant()->getProducts()[stoi(idprod)-1]->getPrice() < 0) {
			cout << "Invalid choice. Please choose available product:" << endl;
			getline(cin, idprod);
		}

		cout << "How many " << d.getRestaurant()->getProducts()[stoi(idprod) - 1]->getName() << " do you wish to order?" << endl;
		getline(cin, quan);


		while (stoi(quan) < 1) {
			cout << "Invalid choice. Please choose a correct quantity:" << endl;
			getline(cin, quan);
		}

		d.addProduct(make_pair(d.getRestaurant()->getProducts()[stoi(idprod) - 1], stoi(quan)));


		cout << "Do you wish to add more products? (y/n)" << endl;
		getline(cin, var);
		while (var != "y" && var != "n") {
			cout << "Invalid option. Do you wish to add more products? (y/n)" << endl;
			getline(cin, var);
		}

	}

	d.setId(deliveries.size() + 1);
	d.calculatePrice();

	var = "u";


	system("CLS");
	cout << "___________Order Info___________" << endl;
	cout << "Restaurant:  " << d.getRestaurant()->getName() << endl;
	cout << endl;
	cout << "Products: " << endl;
	cout << endl;
	for (unsigned int i = 0; i < d.getProducts().size(); i++) {
		cout << d.getProducts()[i].first->getName() << endl;
		cout << "		Quantity: " << d.getProducts()[i].second << endl;
		cout << endl;
	}
	cout << "Price: " << fixed << setprecision(2) << d.getPrice() << endl;
	cout << endl;

	cout << "Confirm order? (y/n) " << endl;
	getline(cin, var);

	while (var != "y" && var != "n") {
		cout << "Invalid option. Confirm order? (y/n)" << endl;
		getline(cin, var);
	}

	if (var == "y") {
		d.setDeliverer(randomDelivererGenerator());
		cout << endl;
		cout << "Your deliverer is: " << d.getDeliverer()->getName() << endl;
		cout << endl;

		pair<Time, Date> t = deliveryTime(client->getMunicipality(), d.getRestaurant()->getAddress()->getMunicipality());
		d.setTime(t.first);
		d.setDate(new Date(t.second));

		cout << "Your delivery arrives at " << setw(2) << setfill('0') << t.first.hour << ":" << setw(2) << setfill('0') << t.first.min << " - " << t.second << setw(1)<<setfill(' ')<<endl;


		cout << endl;
		cout << "Did you receive your order? (y/n)" << endl;
		getline(cin, received);

		while (received != "y" && received != "n") {
			cout << "Invalid option. Did you receive your order? (y/n)" << endl;
			getline(cin, received);
		}

		if (received == "y") {
			d.setOk(true);

			increaseKm(d.getClient(), d.getRestaurant(), d.getDeliverer()->getVehicle());

			cout << "Do you wish to rate your order? (y/n)" << endl;
			getline(cin, var);
			while (var != "y" && var != "n") {
				cout << "Invalid option. Rate order? (y/n)" << endl;
				getline(cin, var);
			}

			if (var == "y") {
				d.setRated(true);

				cout << "Please input your rating: (from 0.00 to 5.00)" << endl;
				getline(cin, var);
				while (!isFloat(var) || stof(var) > 5.00 || stof(var) < 0) {
					cout << endl;
					cout << "Invalid Rating. Please rate again:" << endl;
					getline(cin, var);
				}

				d.setRating(stof(var));


			}
			else if (var == "n") {
				d.setRated(false);
			}

			cout << "Do you wish to add any comment? (y/n)" << endl;
			getline(cin, comment);
			while (comment != "y" && comment != "n") {
				cout << "Invalid option. Add comment to order? (y/n)" << endl;
				getline(cin, comment);
			}

			if (comment == "y") {
				cout << "Write your comment. (Enter to submit)" << endl;
				getline(cin, comment);
				d.setOccurrence(comment);
				cout << endl;
			}
			else if (comment == "n") {
				cout << "Returning to menu" << endl;
				cout << endl;
				d.setOccurrence("No comments");
			}

		}
		else if (received == "n") {
			d.setOccurrence(randomMotiveGenerator());
			d.setOk(false);
			d.setRated(false);
		}

		insertDelivery(new Delivery(d));


	}
	else if (var == "n") {
		cout << endl;
		cout << "Returning to menu...";
	
	
	}
	Sleep(200);
	cout << ".";
	Sleep(200);
	cout << ".";
	Sleep(200);
	cout << ".";
	Sleep(200);
	cout << ".";
	Sleep(200);
	cout << ".";
	system("cls");
	return 0;
}

int Base::restaurantSearcher(Client *c) { 
	
	float lowprice, highprice;
	int count = 0;
	string option,rname,var="y",cuisine,price,option2;
	bool found=false;
	vector <Restaurant*> res;
	vector<string> types;
	
	while (option != "0") {
		
		var = "y";

		cout << "____________Search Restaurant____________" << endl;
		cout << endl;
		cout << "1: Nearby restaurants" << endl << "2: Search restaurant by name" << endl << "3: Search restaurants by cuisine" << endl << "4: Search restaurants by price range" << endl << endl << "0: Go back";
		cout << endl;
		getline(cin, option);

		if ((!isNumber(option)) || (option != "0" && option != "1" && option != "2" && option != "3" && option != "4")) {
			cout << "Not a valid option, please try again" << endl;
			continue;
		}
		switch (stoi(option)) {
			case 1:

				cout << endl;
				cout << endl << "________Results________" << endl;
				for (unsigned int i = 0; i < restaurants.size(); i++) {
					if (c->getMunicipality() == restaurants[i]->getAddress()->getMunicipality()) {
						count++;
						cout << "-> " << restaurants[i]->getName();
						if (((restaurants[i]->getClose().hour > currentTimeNDate().first.hour) && (currentTimeNDate().first.hour > 10)) || (restaurants[i]->getClose().hour < 10 && currentTimeNDate().first.hour < restaurants[i]->getClose().hour) || (restaurants[i]->getClose().hour < 10 && currentTimeNDate().first.hour > restaurants[i]->getClose().hour && currentTimeNDate().first.hour > 10) || ((restaurants[i]->getClose().hour == currentTimeNDate().first.hour) && (restaurants[i]->getClose().min > currentTimeNDate().first.min))) {
							cout << endl;
						}
						else {
							cout << "	CLOSED" << endl;
						}
						found = true;
					}
				}

				count = 0;

				if (!found) {
					cout << "No nearby restaurants found." << endl;
				}

				if (found) {
					cout << endl;
					cout << "Do you wish to order? (y/n)" << endl;
					getline(cin, var);

					while (var != "y" && var != "n") {
						cout << "Invalid option. Do you wish to order? (y/n)" << endl;
						getline(cin, var);
					}

					if (var == "y") {
						Order(c);
						break;
					}
					else if (var == "n") {
						system("CLS");
						break;
					}
				}
			

			case 2:
				while (var == "y") {
					cout << endl;
					cout << "Please input the name of the restaurant you wish to search for:" << endl;
					getline(cin, rname);
					replaceAccent(rname);
					cout << endl << "________Results________" << endl;
					for (unsigned int i = 0; i < restaurants.size(); i++) {
						if (compare_str(rname, restaurants[i]->getName())) {
							count++;
							cout << " -> " << restaurants[i]->getName();
							if (((restaurants[i]->getClose().hour > currentTimeNDate().first.hour) && (currentTimeNDate().first.hour > 10)) || (restaurants[i]->getClose().hour < 10 && currentTimeNDate().first.hour < restaurants[i]->getClose().hour) || (restaurants[i]->getClose().hour < 10 && currentTimeNDate().first.hour > restaurants[i]->getClose().hour && currentTimeNDate().first.hour > 10) || ((restaurants[i]->getClose().hour == currentTimeNDate().first.hour) && (restaurants[i]->getClose().min > currentTimeNDate().first.min))) {
								cout << endl;
							}
							else {
								cout << "   CLOSED" << endl;
							}
							found = true;
						}
					}

					count = 0;

					if (!found) {
						cout << "No restaurants found. Do you wish to search by name again? (y/n)" << endl;
						getline(cin, var);

						while (var != "y" && var != "n") {
							cout << "Invalid option. Search again? (y/n)" << endl;
							getline(cin, var);
						}

						if (var == "y") {
							continue;
						}
						else if (var == "n") {
							break;
						}
					}

					if (found) {
						cout << endl;
						cout << "Do you wish to order? (y/n)" << endl;
						getline(cin, var);

						while (var != "y" && var != "n") {
							cout << "Invalid option. Do you wish to order? (y/n)" << endl;
							getline(cin, var);
						}

						if (var == "y") {
							Order(c);
							break;
						}
						else if (var == "n") {
							system("CLS");
							break;
						}
					}
				}
				break;

			case 3:

				system("CLS");

				cout << "_________List of all types available_________" << endl;

				types=getTypesOrdered();
				
				for (unsigned int i = 0; i < types.size();i++) {
					count++;
					cout << count << " - " << types[i] << endl;
				}

				count = 0;

				
				cout << endl << "Which type of cuisine do you wish to search for? (select number)" << endl;
				getline(cin, cuisine);
				
				while (!isNumber(cuisine) || (stoi(cuisine) > getTypesOrdered().size()-1) && stoi(cuisine) < 0) {
					cout << endl << "Invalid input. Please select available type: (select number)" << endl;
					getline(cin, cuisine);
				}

				cuisine = getTypesOrdered()[stoi(cuisine)-1];
				res = searchByCuisine(cuisine);

				if (res.size() == 0) {
					cout << "No results found" << endl << endl;
					break;
				}
				
				
				for (unsigned int i = 0; i < res.size(); i++){
					cout << " -> " << res[i]->getName();
					found = true;
					if (((restaurants[i]->getClose().hour > currentTimeNDate().first.hour) && (currentTimeNDate().first.hour > 10)) || (restaurants[i]->getClose().hour < 10 && currentTimeNDate().first.hour < restaurants[i]->getClose().hour) || (restaurants[i]->getClose().hour < 10 && currentTimeNDate().first.hour > restaurants[i]->getClose().hour && currentTimeNDate().first.hour>10) || ((restaurants[i]->getClose().hour == currentTimeNDate().first.hour) && (restaurants[i]->getClose().min > currentTimeNDate().first.min))) {
						cout << endl;
					}
					else {
						cout << "   CLOSED" << endl;
					}
				}
				
				
				if (found) {
					cout << endl;
					cout << "Do you wish to order? (y/n)" << endl;
					getline(cin, var);

					while (var != "y" && var != "n") {
						cout << "Invalid option. Do you wish to order? (y/n)" << endl;
						getline(cin, var);
					}

					if (var == "y") {
						Order(c);
						break;
					}
					else if (var == "n") {
						system("CLS");
						break;
					}
				}
				break;

			case 4:
				system("CLS");

				while (option2 != "0") {

					var = "y"; // resets var

					cout << "________Search by price range________" << endl;
					cout << "1: Search for restaurants with average price below given price\n2: Search for restaurants with average price above given price\n3: Search for restaurants with average price in given price range\n\n0:Go Back" << endl;
					getline(cin, option2);

					if ((!isNumber(option2)) || (option2 != "0" && option2 != "1" && option2 != "2" && option2 != "3")) {
						cout << "Not a valid option, please try again" << endl;
						continue;
					}

					switch (stoi(option2)) {

					case 1:
						cout << "Please give highest average price:" << endl;
						getline(cin, price);
						highprice = stof(price);


						while (!isFloat(price)) {
							cout << "Highest price has to be a number. Please input highest price again:" << endl;
							getline(cin, price);
							highprice = stof(price);
						}

						while (var == "y") {

							cout << endl << "________Results________" << endl;

							for (auto a: restaurantsLowerThan(highprice)) {
								found = true;
								count++;
								cout << " -> " << a->getName();
								if (((a->getClose().hour > currentTimeNDate().first.hour) && (currentTimeNDate().first.hour > 10)) || (a->getClose().hour < 10 && currentTimeNDate().first.hour < a->getClose().hour) || (a->getClose().hour < 10 && currentTimeNDate().first.hour > a->getClose().hour && currentTimeNDate().first.hour > 10) || ((a->getClose().hour == currentTimeNDate().first.hour) && (a->getClose().min > currentTimeNDate().first.min))) {
									cout << endl;
								}
								else {
									cout << "   CLOSED" << endl;
								}
								
							}
							

							count = 0;
							var = "n";

							if (!found) {
								cout << "No results found" << endl << endl;
								cout << endl << "Do you wish to search again?(y/n)" << endl;
								getline(cin, var);

								while (var != "y" && var != "n") {
									cout << "Invalid option. Do you wish to search again? (y/n)" << endl;
									getline(cin, var);
								}

								if (var == "y") {
									continue;
								}
								else if (var == "n") {
									system("CLS");
									break;
								}
							}
							if (found) {
								cout << endl;
								cout << "Do you wish to order? (y/n)" << endl;
								getline(cin, var);

								while (var != "y" && var != "n") {
									cout << "Invalid option. Do you wish to order? (y/n)" << endl;
									getline(cin, var);
								}

								if (var == "y") {
									Order(c);
									break;
								}
								else if (var == "n") {
									system("CLS");
									break;
								}
							}
						}

						break;

					case 2:
						cout << "Please give lowest average price:" << endl;
						getline(cin, price);
						lowprice = stof(price);

						while (!isFloat(price)) {
							cout << "Lowest price has to be a number. Please input lowest price again:" << endl;
							getline(cin, price);
							lowprice = stof(price);
						}

						while (var == "y") {

							cout << endl << "________Results________" << endl;

							for (auto a: restaurantsHigherThan(lowprice)) {
								
								found = true;
								count++;
								cout << " -> " << a->getName();
								if (((a->getClose().hour > currentTimeNDate().first.hour) && (currentTimeNDate().first.hour > 10)) || (a->getClose().hour < 10 && currentTimeNDate().first.hour < a->getClose().hour) || (a->getClose().hour < 10 && currentTimeNDate().first.hour > a->getClose().hour && currentTimeNDate().first.hour > 10) || ((a->getClose().hour == currentTimeNDate().first.hour) && (a->getClose().min > currentTimeNDate().first.min))) {
									cout << endl;
								}
								else {
									cout << "   CLOSED" << endl;
								}
								
							}
							system("pause");

							count = 0;
							var = "n";

							if (!found) {
								cout << "No results found" << endl << endl;
								cout << endl << "Do you wish to search again?(y/n)" << endl;
								getline(cin, var);

								while (var != "y" && var != "n") {
									cout << "Invalid option. Do you wish to search again? (y/n)" << endl;
									getline(cin, var);
								}

								if (var == "y") {
									continue;
								}
								else if (var == "n") {
									system("CLS");
									break;
								}
							}
							if (found) {
								cout << endl;
								cout << "Do you wish to order? (y/n)" << endl;
								getline(cin, var);

								while (var != "y" && var != "n") {
									cout << "Invalid option. Do you wish to order? (y/n)" << endl;
									getline(cin, var);
								}

								if (var == "y") {
									Order(c);
									break;
								}
								else if (var == "n") {
									system("CLS");
									break;
								}
							}
						}

						break;
					case 3:
						cout << "Please give lowest price:" << endl;
						getline(cin, price);
						lowprice = stof(price);

						while (!isFloat(price)) {
							cout << "Lowest price has to be a number. Please input lowest price again:" << endl;
							getline(cin, price);
							lowprice = stof(price);
						}

						cout << "Please give highest price:" << endl;
						getline(cin, price);
						highprice = stof(price);

						while (!isFloat(price)) {
							cout << "Highest price has to be a number. Please input highest price again:" << endl;
							getline(cin, price);
							highprice = stof(price);
						}

						while (lowprice > highprice) {
							cout << "Lower price can´t be bigger than higher price. Please input high price again:" << endl;
							getline(cin, price);
							highprice = stof(price);
						}

						while (var == "y") {

							cout << endl << "________Results________" << endl;

							for (auto a: restaurantsBetween(lowprice,highprice)) {
								
								found = true;
								count++;
								cout << " -> " << a->getName();
								if (((a->getClose().hour > currentTimeNDate().first.hour) && (currentTimeNDate().first.hour > 10)) || (a->getClose().hour < 10 && currentTimeNDate().first.hour < a->getClose().hour) || (a->getClose().hour < 10 && currentTimeNDate().first.hour > a->getClose().hour && currentTimeNDate().first.hour>10) || ((a->getClose().hour == currentTimeNDate().first.hour) && (a->getClose().min > currentTimeNDate().first.min))) {
									cout << endl;
								}
								else {
									cout << "   CLOSED" << endl;
								}
								
							}
							system("pause");

							count = 0;
							var = "n";

							if (!found) {
								cout << "No results found" << endl << endl;
								cout << endl << "Do you wish to search again?(y/n)" << endl;
								getline(cin, var);

								while (var != "y" && var != "n") {
									cout << "Invalid option. Do you wish to search again? (y/n)" << endl;
									getline(cin, var);
								}

								if (var == "y") {
									continue;
								}
								else if (var == "n") {
									system("CLS");
									break;
								}
							}
							if (found) {
								cout << endl;
								cout << "Do you wish to order? (y/n)" << endl;
								getline(cin, var);

								while (var != "y" && var != "n") {
									cout << "Invalid option. Do you wish to order? (y/n)" << endl;
									getline(cin, var);
								}

								if (var == "y") {
									Order(c);
									break;
								}
								else if (var == "n") {
									system("CLS");
									break;
								}
							}

						}
						break;

					case 0:
						system("CLS");
						break;

					}
				}
				break;
			
			case 0:
				system("CLS");
				return 0;
		}
	}
	return 0;

}

int Base::clientEditer(Client *client) {

	string var = "y", option2, name, pass, pass2, ad, address, a = "";
	
	bool leave = false;
	int key = 0;
	int c = 0;
	int count = 0;
	while (option2 != "0") {
		system("CLS");
		cout << "Which info do you wish to edit?" << endl;
		cout << "1: Name \n2: Address \n3: Password \n\n0: Go Back" << endl;
		getline(cin, option2);

		if ((!isNumber(option2)) || (option2 != "0" && option2 != "1" && option2 != "2" && option2 != "3")) {
			cout << "Not a valid option, please try again" << endl;
			continue;
		}
		string a = "";
		int key = 0;
		int nrcouts = 0;
		bool temp = false;
		switch (stoi(option2)) {
		case 1:
			cout << "Input new name: " << endl;
			getline(cin, name);
			replaceAccent(ad);
			while (!isWord(name)) {
				cout << "Name not in right format. Try again:" << endl;
				getline(cin, name);
			}

			client->setName(name);
			cout << "New name set" << endl;
			system("pause");
			break;

		case 2:

			cout << "Input your street:" << endl;
			getline(cin, ad);
			replaceAccent(ad);
			while (!isStreet(ad)) {
				cout << "Street in wrong format. Try again:" << endl;
				getline(cin, ad);
			}
			address = ad;

			cout << "Input door number:" << endl;
			getline(cin, ad);
			replaceAccent(ad);
			while (!isStreet(ad)) {
				cout << "Door number needs to be a number. Input door number again:" << endl;
				getline(cin, ad);
			}
			address = address + ", " + ad;

			cout << "Input ZipCode:" << endl;
			getline(cin, ad);
			while (!isPostalCode(ad)) {
				cout << "ZipCode is in wrong format (xxxx-xxx). Input ZipCode again:" << endl;
				getline(cin, ad);
			}
			address = address + ", " + ad;

			cout << "Input Municipality:" << endl;
			getline(cin, ad);
			replaceAccent(ad);
			while (!isWord(ad)) {
				cout << "Municipality has to be a word. Please input again:" << endl;
				getline(cin, ad);
				replaceAccent(ad);
			}
			while (!compare_str(ad, getMunicipality()) && find(neighbouring.begin(), neighbouring.end(), ad) == neighbouring.end()) {
				cout << "Municipality not covered! Municipalities covered:" << endl;
				cout << " -> " << getMunicipality() << endl;
				for (unsigned int i = 0; i < neighbouring.size(); i++) {
					cout << " -> " << neighbouring[i] << endl;
				}
				cout << "Please input a municipality listed above:" << endl;
				getline(cin, ad);
			}
			address = address + ", " + ad;

			client->setAddress(new Address(address));
			cout << "New address set." << endl;
			system("pause");

			break;

		case 3:

			system("CLS");
			cout << "Input new password: " << endl;

		
			pass = read_pass();


			cout << endl << "Confirm new password: " << endl;
			pass2 = read_pass();
			while (!compare_str(pass,pass2)) {
				cout << endl << "Passwords don't match. Please confirm pass again (0 + Enter to cancel)" << endl;
		

				
				
				pass2 = read_pass();
				if (pass2 == "0") {
					cout << endl << "Error setting password" << endl;
					leave = true;
					break;
				}
			}

			if (leave)break;


			client->setPassword(pass);

			cout << endl << "New password set" << endl;
			system("pause");
			break;

		case 0:
			system("CLS");
			return 0;

		}

	}
	return 0;
}

int Base:: clientInterfaceMenu(Client* client) {
	
	string option,var="y",option2,name,pass,pass2,ad,address,a="";
	
	bool leave=false;
	int key = 0;
	sorterC();
	
	//int index = search(client, clients);
	//cout << index;
	
	


	while (option != "0") {
		
		cout << "__________What would you like to do?__________" << endl;
		cout << "1: Order food\n2: Search for restaurant \n3: See list of previous orders\n4: Edit info\n5: Delete account\n\n0: Exit menu" << endl;
		getline(cin, option);

		if ((!isNumber(option)) || (option != "0" && option != "1" && option != "2" && option != "3"&& option != "4" && option != "5")) {
			cout << "Not a valid option, please try again" << endl;
			continue;
		}
		unsigned int k = 0;
		switch (stoi(option)) {
			
			case 1:
				system("CLS");

				Order(client);
				
				break;
			case 2:
				system("CLS");
				restaurantSearcher(client);
				break;

			case 3:
				system("CLS");
				cout << "____________Previous orders____________" << endl;
				
				client->orderViewer();
				cout << endl;
				cout << endl;
				system("pause");
				system("CLS");
				break;


			case 4:
				clientEditer(client);
				break;

			case 5:
				cout << "Are you sure? All data will be lost! (y/n)" << endl;
				getline(cin, var);

				while (var != "y" && var != "n") {
					cout << "Invalid option. Are you sure you want to delete your account? (y/n)" << endl;
					getline(cin, var);
				}

				if (var == "y") {
					client->setErased(true);
				}
				else {
					system("CLS");
					return 0;
				}
				break;
			
			case 0:
				system("CLS");
				
				return 0;


		}
	}
	return 0;
}   


int Base::newEmployee() {

	bool sena = true, found = false, checkem = false, pls = true, golfCar, isAdmin;
	Employee e;
	Admin a;
	Deliverer d;
	Vehicle v;
	Date date;
	string pName, pNif, pPass, pDate, pSalary, newE, a2, a1;
	vector<string> vNewE, va2, va1;

	while (sena) {
		checkem = false;
		cout << "Insert employee's name: ";
		getline(cin, newE);
		replaceAccent(newE);
		vNewE = decompose(newE, ' ');
		for (unsigned int i = 0; i < vNewE.size(); i++) {
			if (!isWord(vNewE[i])) {
				cout << "\nNot a valid input" << endl;
				vNewE.clear();
				checkem = true;
				break;
			}
		}
		if (checkem) continue;
		pName = newE;
		sena = false;
	}

	sena = true;

	while (sena) {
		cout << "\nInsert employee's NIF: ";
		getline(cin, newE);
		trim(newE);
		if (!isNumber(newE) || newE.length() != 9) {
			cout << "\nNot a valid NIF, please try again" << endl;
			continue;
		}
		pNif = newE;
		sena = false;
	}

	for (unsigned int i = 0; i < employees.size(); i++) {
		if (employees[i]->getNif() == stoi(pNif)) {
			found = true;
			break;
		}
	}

	if (found) {
		cout << "\nThis employee already exists so it is not possible to add them again." << endl;
		return 1;
	}

	sena = true;

	while (sena) {
		cout << "\nWill this employee be \n1: An Admin \n2: A Deliverer \n\n0: Quit this action and return to Employee Menu (this employee will not be added)" << endl;
		getline(cin, newE);
		trim(newE);

		if (newE == "0") {
			return 1;
		}
		if (newE == "2") {
			checkem = false;
			isAdmin = false;
			d.setName(pName);
			d.setNif(stoi(pNif));


			cout << "\nAbout the employee's vehicle, ";

			while (true) {
				cout << "please insert the brand: ";
				getline(cin, a2);
				trim(a2);
				va2 = decompose(a2, ' ');

				for (unsigned int j = 0; j < va2.size(); j++) {
					if (!isPass(va2[j])) {
						cout << "\nNot a valid input, please do not include acutes, tilde, etc" << endl;
						va2.clear();
						checkem = true;
						break;
					}
				}
				if (checkem) continue;
				v.setBrand(a2);
				va2.clear();
				break;
			}

			while (true) {
				checkem = false;
				cout << "\nplease insert the vehicle's model: ";
				getline(cin, a2);
				trim(a2);
				va2 = decompose(a2, ' ');

				for (unsigned int j = 0; j < va2.size(); j++) {
					if (!isPass(va2[j])) {
						cout << "\nNot a valid input, please do not include acutes, tilde, etc" << endl;
						va2.clear();
						checkem = true;
					}
				}
				if (checkem) continue;
				v.setModel(a2);
				va2.clear();
				break;
			}
			checkem = false;

			while (true) {
				cout << "\nplease isnsert the vehicle's date of acquisition: ";

				getline(cin, a2);

				if (!isDateFormat(a2) || !checkDate(new Date(a2))) {
					cout << "\nNot a valid date, please use the format Day/Month/Year" << endl;
					continue;
				}

				va2 = decompose(a2, '/');
				date.setDay(stoi(va2[0]));
				date.setMonth(stoi(va2[1]));
				date.setYear(stoi(va2[2]));
				v.setAquisition(new Date(date));
				break;
			}


			sena = false;
			break;
		}

		if (newE == "1") {

			a.setName(pName);
			a.setNif(stoi(pNif));
			isAdmin = true;

			pls = true;

			while (pls) {
				checkem = false;
				cout << "\nInsert the Admin's job: ";

				getline(cin, a1);
				trim(a1);
				va1 = decompose(a1, ' ');

				for (unsigned int j = 0; j < va1.size(); j++) {
					if (!isWord(va1[j])) {
						cout << "\nNot a valid input, please do not include any numbers, acutes, etc" << endl;
						checkem = true;
						break;
					}
				}

				if (checkem) continue;


				a.setAJob(a1);
				pls = false;
				break;
			}

			while (true) {
				cout << "\nWhat vehicle will this Admin be given?" << endl;
				cout << "1: The default vehicle \n2: Another vehicle...." << endl;
				getline(cin, a1);
				trim(a1);
				if (a1 == "1") {
					cout << "\nSet as default vehicle (this can be changed later)" << endl;
					golfCar = true;
					sena = false;
					break;
				}
				else if (a1 == "2") {
					golfCar = false;
					cout << "\nAbout the employee's vehicle, ";

					while (true) {
						cout << "please insert the brand: ";
						getline(cin, a2);
						trim(a2);
						va2 = decompose(a2, ' ');

						for (unsigned int j = 0; j < va2.size(); j++) {
							if (!isPass(va2[j])) {
								cout << "\nNot a valid input, please do not include acutes, tilde, etc" << endl;
								va2.clear();
								checkem = true;
								break;
							}
						}
						if (checkem) continue;
						v.setBrand(a2);
						va2.clear();
						break;
					}

					while (true) {
						checkem = false;
						cout << "\nplease insert the vehicle's model: ";
						getline(cin, a2);
						trim(a2);
						va2 = decompose(a2, ' ');

						for (unsigned int j = 0; j < va2.size(); j++) {
							if (!isPass(va2[j])) {
								cout << "\nNot a valid input, please do not include acutes, tilde, etc" << endl;
								va2.clear();
								checkem = true;
							}
						}
						if (checkem) continue;
						v.setModel(a2);
						va2.clear();
						break;
					}
					checkem = false;

					while (true) {
						cout << "\nplease isnsert the vehicle's date of acquisition: ";

						getline(cin, a2);

						if (!isDateFormat(a2) || !checkDate(new Date(a2))) {
							cout << "\nNot a valid date, please use the format Day/Month/Year" << endl;
							continue;
						}

						va2 = decompose(a2, '/');
						date.setDay(stoi(va2[0]));
						date.setMonth(stoi(va2[1]));
						date.setYear(stoi(va2[2]));
						v.setAquisition(new Date(date));
						break;
					}


					sena = false;

					break;



				}

			}


		}
		if (newE != "0" && newE != "1" && newE != "2") {
			cout << "\nNot a valid input, please try again" << endl;
			continue;
		}
	}


	sena = true;
	checkem = false;

	while (sena) {
		cout << "\nChoose a temporary password for employee (they will be able to change it later): ";
		getline(cin, newE);
		replaceAccent(newE);
		if (!isPass(newE)) {
			cout << "Not a valid password" << endl;
			continue;
		}
		pPass = newE;
		sena = false;
	}




	sena = true;
	checkem = false;

	while (sena) {
		cout << "\nInsert employee's birth date: ";
		getline(cin, newE);
		if (!isDateFormat(newE) || !checkDate(new Date(newE))) {
			cout << "Not a valid date, please use the format Day/Month/Year" << endl;
			continue;
		}
		pDate = newE;
		sena = false;
	}

	sena = true;

	while (sena) {
		cout << "\nInsert the emplyoee's salary: ";
		getline(cin, newE);
		if (!isFloat(newE)) {
			cout << "Not a valid input, it must be a number in the format 'xxxx.xx'" << endl;
			continue;
		}
		pSalary = newE;
		sena = false;
	}

	sena = true;
	checkem = false;



	if (!isAdmin) {
		d.setDate(new Date(pDate));
		d.setPassword(pPass);
		d.setSalary(stof(pSalary));
		d.setVehicle(new Vehicle(v));
		if (!addEmployee(new Deliverer(d))) {
			cout << "\nThere was an error adding this employee" << endl;
			return 1;
		}
		else {
			cout << "\nDeliverer added with success" << endl;
			return 0;
		}
	}
	else if (isAdmin) {
		a.setDate(new Date(pDate));
		a.setPassword(pPass);
		a.setSalary(stof(pSalary));

		if (!golfCar) a.setVehicle(new Vehicle(v));

		if (!addEmployee(new Admin(a))) {
			cout << "\nThere was an error adding this employee" << endl;
			return 1;
		}
		else {
			cout << "\nAdmin added with success" << endl;
			return 0;
		}
	}
}

int Base::employeeMenu(Employee* bossW) {
	string option = "";

	system("cls");

	if (!compare_str("Boss", bossW->getAJob())) {
		cout << "\nYou do not have permission to do this" << endl;
		return 1;
	}
	
	while (option != "0") {
		cout << "__________Employing Menu__________" << endl<<endl;
		cout << "1 - Reemploy old employee (recommended)" << endl << "2 - Employ someone new" << endl << endl << "0 - Go Back" << endl << endl;
		getline(cin, option);

		if (option == "0")return 1;
		while (!isNumber(option) || stoi(option) > 2 || stoi(option) < 0) {
			cout << "Invalid Option: please try again." << endl;
			getline(cin, option);
		}

		switch (stoi(option)) {
		case 1:
			//HASHTABLES
			
			
			
			break;


		case 2:
			newEmployee();
			break;

		case 0:
			return 1;
		}
	}

	return 1;
}

int Base::editProduct(string resEdit) {

	string cic = "", in, re, gonfirm;
	bool notOk = true, adP;
	Restaurant* r = restaurants[stoi(resEdit) - 1];
	Product p;


	while (cic != "end2") {
		cout << "\nWhat would you like to do \n1: Remove a product \n2: Add a product \n3: Change a product's price \n\n0: Exit (changes made will be saved)" << endl;
		getline(cin, gonfirm);

		if (!isNumber(gonfirm)) {
			cout << "Not a valid input" << endl;
			continue;
		}

		switch (stoi(gonfirm)) {
		case 1:
			for (unsigned int i = 0; i < r->getProducts().size(); i++) {
				cout << i + 1;
				cout << " - ";
				cout << *r->getProducts()[i] << endl;
			}

			cout << "Input number ID of product you wish to remove" << endl;
			while (notOk) {

				getline(cin, re);

				if (!isNumber(re) || (stoi(re) - 1) > restaurants.size()) {
					cout << "Not a valid input" << endl;
					continue;
				}

				r->removeProduct(re);
				notOk = false;
			}
			break;

		case 2:

			cout << "To add a product:" << endl;

			adP = true;
			while (adP) {
				while (cic != "end2") {
					cout << "Please insert the product's name:" << endl;
					getline(cin, in);
					if (!isStreet(in)) {
						cout << "Not a valid name" << endl;
						continue;
					}
					p.setName(in);
					cic = "end2";
				}
				while (cic != "end2.1") {
					cout << "Please insert the product's price:" << endl;
					getline(cin, in);
					if (!isFloat(in)) {
						cout << "Not a valid price" << endl;
						continue;
					}
					p.setPrice(stof(in));
					cic = "end2.1";
				}
				while (cic != "end2.2") {
					cout << "Please insert the product's type (eg. Vegetarian):" << endl;
					getline(cin, in);
					if (!isWord(in)) {
						cout << "Not a valid type" << endl;
						continue;
					}
					p.setType(in);
					cic = "end2.2";
				}

				r->addProducts(new Product(p));
				adP = false;

			}
			break;

		case 3:
			adP = true;
			while (adP) {

				cout << "To what would you like to change the product's price to?" << endl;
				getline(cin, re);

				if (!isFloat(re) || stof(re) <= 0) {
					cout << "Not a valid input" << endl;
					continue;
				}

				p.setPrice(stof(in));
				r->addProducts(new Product(p));
				adP = false;
			}

			break;


		case 0:

			cic = "end2";
			system("CLS");
			return 0;
		}


	}



	return 0;
}

int Base::resEdit() {

	bool ok;
	string resEdit, choose, cic = "", in;
	vector<string> v;
	Time t;

	for (unsigned int i = 0; i < restaurants.size(); i++) {
		cout << i + 1;
		cout << "\n";
		cout << *restaurants[i] << endl;
		cout << "\n\n\n";
	}
	ok = true;
	while (ok) {
		cout << "\nInput number ID of restaurant you wish to edit" << endl;
		getline(cin, resEdit);
		if (!isNumber(resEdit) || stoi(resEdit) - 1 > restaurants.size()) {
			cout << "Not a valid input" << endl;
			continue;
		}
		ok = false;
	}
	ok = true;
	while (ok) {
		cout << "\nWhat would you like to edit \n1: Products \n2: Closing time \n0: Exit (changes will be saved)" << endl;
		getline(cin, choose);
		if (!isNumber(choose)) {
			cout << "Not a valid input" << endl;
			continue;
		}

		switch (stoi(choose)) {
		case 2:

			while (cic != "end1") {
				cout << "Insert the restaurant's closing time (in format xx:xx)" << endl;
				getline(cin, in);
				if (in.length() != 5 || in[2] != ':') {
					cout << "Not a valid input, please try again" << endl;
					continue;
				}
				v = decompose(in, ':');
				if (!isNumber(v[0]) || !isNumber(v[1])) {
					cout << "Not a valid input, please try again" << endl;
					continue;
				}
				if (stoi(v[0]) < 0 || stoi(v[0]) > 24 || stoi(v[1]) < 0 || stoi(v[1]) > 59) {
					cout << "Not a valid time, please try again" << endl;
					continue;
				}
				t.hour = stoi(v[0]);
				t.min = stoi(v[1]);
				restaurants[stoi(resEdit) - 1]->setClose(t);
				cic = "end1";
			}


			ok = false;
			break;

		case 1:


			if (editProduct(resEdit) != 0) {
				cout << "Error editing" << endl;

			}
			else if (editProduct(resEdit) == 0) {
				cout << "Edited" << endl;
			}


			break;

		case 0:
			return 0;
		}


	}


	return 1;
}

int Base::resAdder() {

	Time t;
	string in = "", ad, address, cic = "";
	Restaurant r;
	vector<string> v;
	Product p;
	bool adP;

	while (cic != "end0") {
		cout << "\nInsert new restaurant's name: " << endl;
		getline(cin, in);
		replaceAccent(in);
		if (!isStreet(in)) {
			cout << "Not a valid name" << endl;
			continue;
		}
		r.setName(in);
		cic = "end0";
	}


	cout << "Input the restaurant's street:" << endl;
	getline(cin, ad);
	replaceAccent(ad);
	while (!isStreet(ad)) {
		cout << "Street in wrong format. Try again:" << endl;
		getline(cin, ad);
	}
	address = ad;

	cout << "Input door number:" << endl;
	getline(cin, ad);
	replaceAccent(ad);
	while (!isNumber(ad)) {
		cout << "Door number needs to be a number. Input door number again:" << endl;
		getline(cin, ad);
	}
	address = address + ", " + ad;

	cout << "Input ZipCode:" << endl;
	getline(cin, ad);

	while (!isPostalCode(ad)) {
		cout << "ZipCode is in wrong format (xxxx-xxx). Input ZipCode again:" << endl;
		getline(cin, ad);
	}
	address = address + ", " + ad;

	cout << "Input Municipality:" << endl;
	getline(cin, ad);
	replaceAccent(ad);
	while (!isWord(ad)) {
		cout << "Municipality has to be a word. Please input again:" << endl;
		getline(cin, ad);
	}
	while (!compare_str(ad, getMunicipality()) && find(neighbouring.begin(), neighbouring.end(), ad) == neighbouring.end()) {
		cout << "Municipality not covered! Municipalities covered:" << endl;
		cout << " -> " << getMunicipality() << endl;
		for (unsigned int i = 0; i < neighbouring.size(); i++) {
			cout << " -> " << neighbouring[i] << endl;
		}
		cout << "Please input a municipality listed above:" << endl;
		getline(cin, ad);
	}
	address = address + ", " + ad;

	r.setAddress(address);
	cout << "\nNew address set." << endl;

	while (cic != "end1") {
		cout << "Insert the restaurant's closing time (in format xx:xx)" << endl;
		getline(cin, in);
		if (in.length() != 5 || in[2] != ':') {
			cout << "Not a valid input, please try again" << endl;
			continue;
		}
		v = decompose(in, ':');
		if (!isNumber(v[0]) || !isNumber(v[1])) {
			cout << "Not a valid input, please try again" << endl;
			continue;
		}
		if (stoi(v[0]) < 0 || stoi(v[0]) > 24 || stoi(v[1]) < 0 || stoi(v[1]) > 59) {
			cout << "Not a valid time, please try again" << endl;
			continue;
		}
		t.hour = stoi(v[0]);
		t.min = stoi(v[1]);
		r.setClose(t);
		cic = "end1";
	}

	cout << "To add a product:" << endl;

	adP = true;
	while (adP) {
		while (cic != "end2") {
			cout << "Please insert the product's name:" << endl;
			getline(cin, in);
			if (!isStreet(in)) {
				cout << "Not a valid name" << endl;
				continue;
			}
			p.setName(in);
			cic = "end2";
		}
		while (cic != "end2.1") {
			cout << "Please insert the product's price:" << endl;
			getline(cin, in);
			if (!isFloat(in)) {
				cout << "Not a valid price" << endl;
				continue;
			}
			p.setPrice(stof(in));
			cic = "end2.1";
		}
		while (cic != "end2.2") {
			cout << "Please insert the product's type (eg. Vegetarian):" << endl;
			getline(cin, in);
			if (!isWord(in)) {
				cout << "Not a valid type" << endl;
				continue;
			}
			p.setType(in);
			cic = "end2.2";
		}

		r.addProducts(new Product(p));

		while (true) {
			cout << "Would you like to add another product? (y/n)" << endl;
			getline(cin, in);
			trim(in);
			if (in == "y") break;
			else if (in == "n") {
				adP = false;
				break;
			}
			else {
				cout << "Not a valid input" << endl;
				continue;
			}
		}


	}

	if (addRestaurant(new Restaurant(r))) return 0;
	else return 1;

}



int Base::restaurantMenu() {
	string restaurantOption, resRemove, name;
	Restaurant r;
	bool ok = true, found = false;

	while (restaurantOption != "0") {
		cout << "\n_______Restaurant Menu_______\n" << endl;
		cout << "1: View restaurant list \n2: Add a restaurant \n3: Remove a restaurant \n4: Edit a restaurant's information \n5: View deliveries from given restaurant \n\n0: Exit to main menu" << endl;
		getline(cin, restaurantOption);

		if ((!isNumber(restaurantOption)) || (restaurantOption != "0" && restaurantOption != "1" && restaurantOption != "2" && restaurantOption != "3" && restaurantOption != "4" && restaurantOption != "5")) {
			cout << "Not a valid option, please try again" << endl;
			continue;
		}


		switch (stoi(restaurantOption)) {

		case 1:
			cout << "\n______Restaurant List______" << endl;

			for (unsigned int i = 0; i < restaurants.size(); i++) {
				if (!restaurants[i]->getInactive()) {
					cout << *restaurants[i] << endl;
				}
			}
			system("pause");

			break;

		case 2:
			if (resAdder() != 0) cout << "\nRestaurant was not added" << endl;
			else cout << "\nRestaurant added" << endl;

			break;
		case 3:
			for (unsigned int i = 0; i < restaurants.size(); i++) {
				cout << i + 1;
				cout << "\n";
				cout << *restaurants[i] << endl;
				cout << "\n\n\n";
			}
			ok = true;
			while (ok) {
				cout << "\nInput number ID of restaurant you wish to remove from database" << endl;
				getline(cin, resRemove);
				if (!isNumber(resRemove) || stoi(resRemove) - 1 > restaurants.size()) {
					cout << "Not a valid input" << endl;
					continue;
				}

				restaurants[stoi(resRemove) - 1]->setInactive(true);
				ok = false;
				cout << "\nRestaurant removed" << endl;
			}
			break;
		case 4:

			if (resEdit() != 0) cout << "Didn't edit restaurant" << endl;
			else if (resEdit() == 0) cout << "Restaurant edited" << endl;

			break;

		case 5:

			while (name != "0") {

				cout << "Which restaurant do you wish to view deliveries from? (please write name - 0 to leave)" << endl;
				getline(cin, name);

				if (name == "0")break;

				for (unsigned int j = 0; j < restaurants.size(); j++) {
					if (compare_str(restaurants[j]->getName(), name)) {
						r = *restaurants[j];
						found = true;
						name = "0";
						break;
					}
				}

				if (!found) {
					cout << "Restaurant not found. Try again:" << endl;
					continue;
				}
			}

			for (unsigned int i = 0; i < deliveries.size(); i++) {
				if (*deliveries[i]->getRestaurant() == r) {
					cout << *deliveries[i] << endl;
				}
			}

			break;
		case 0:
			system("CLS");
			return 0;

		}
	}
	return 0;

}

int Base::clientMenu() {
	string clientOption, blacklistOption = "5", nif;
	bool found = false;
	Client c;

	while (clientOption != "0") {

		cout << "________Clients Menu________\n" << endl;
		cout << "1: View client list \n2: Add a client to the blacklist \n3: Remove a client from the blacklist \n4: View deliveries from a client \n5:View Blacklist\n\n0: Exit to main menu" << endl;
		getline(cin, clientOption);

		if ((!isNumber(clientOption)) || (clientOption != "0" && clientOption != "1" && clientOption != "2" && clientOption != "3" && clientOption != "4" && clientOption != "5")) {
			cout << "Not a valid option, please try again" << endl;
			continue;
		}

		switch (stoi(clientOption)) {
		case 0:
			system("CLS");
			return 0;

		case 1:

			for (unsigned int i = 0; i < clients.size(); i++) {
				cout << *clients[i] << endl;
			}
			system("pause");
			break;

		case 2:

			nif = "";

			while (nif != "0") {
				cout << "Please input the nif of the client you wish to add to blacklist (0+Enter to leave)" << endl;
				getline(cin, nif);
				while (!isNumber(nif) && nif.length() != 9 && nif != "0") {
					cout << "Invalid NIF. Please input nif in correct format: (0+Enter to leave)" << endl;
					getline(cin, nif);
				}
				if (nif == "0") {
					nif = "";
					break;
				}
				else {
					
					try {
						addClientBlacklist(mstoi(nif));
						nif = "0";
					}
					catch (ClientAlreadyInBlacklist & e) {
						cout << endl << "ClientAlreadyInBlacklist: Returning to menu..." << endl << endl;
					}
					catch (NoClientWithSuchNif & i) {
						cout << endl << "NoClientWithSuchNIF: Client not found. Please try again." << endl;
						found = false;
						continue;
					}
					
					found = true;
					

				}
			}
			break;

		case 3:

			while (blacklistOption != "0") {
				cout << "Would you like to \n1:Add this client to the regular client list \n2:Remove this client from the database entirely \n\n0: Go back" << endl;
				getline(cin, blacklistOption);

				if (blacklistOption == "0") break; 
				else if (blacklistOption == "1") {
					cout << "Please input the nif of the client you wish to edit (0+Enter to leave)" << endl;
					getline(cin, nif);
					while (!isNumber(nif) && nif.length() != 9 && nif != "0") {
						cout << "Invalid NIF. Please input nif in correct format: (0+Enter to leave)" << endl;
						getline(cin, nif);
					}
					if (nif == "0") {
						nif = "";
						continue;
					}
					else {
						try {
							ClientRedemption(mstoi(nif));
						}
						catch (NoClientInBlacklist & e) {
							cout << "NoClientInBlacklist: " << e.getClientNotInBlacklist() << "is not in the blacklist" << endl;
							cout << endl << "Returning to menu... " << endl;
							Sleep(2000);
							continue;
						}
					}


					continue;
				}
				else if (blacklistOption == "2") {
					cout << "Please input the nif of the client you wish to remove: (0+Enter to leave)" << endl;
					getline(cin, nif);
					while (!isNumber(nif) && nif.length() != 9 && nif != "0") {
						cout << "Invalid NIF. Please input nif in correct format: (0+Enter to leave)" << endl;
						getline(cin, nif);
					}
					if (nif == "0") {
						nif = "";
						continue;
					}
					else {
						found = false;
						for (unsigned int i = 0; i < blacklist.size(); i++) {
							if (blacklist[i]->getNif() == stoi(nif)) {
								found = true;
								blacklist[i]->setErased(true);
								cout << endl << "Client removed from database" << endl;
							}
						}
						if (!found) {
							cout << endl << "Could not find client. Please input nif again: (0+Enter to leave)" << endl;
							continue;
						}
					}
					continue;
				}
				else {
					cout << "Not a valid input, please try again" << endl << endl;
					continue;
				}
			}
			blacklistOption = "5";
			break;

		case 4:

			nif = "";

			while (nif != "0") {
				cout << "Please input the nif of the client you wish to view deliveries from:(0+Enter to leave)" << endl;
				getline(cin, nif);
				while (!isNumber(nif) && nif.length() != 9 && nif != "0") {
					cout << "Invalid NIF. Please input nif in correct format: (0+Enter to leave)" << endl;
					getline(cin, nif);
				}
				if (nif == "0") {
					nif = "";
					break;
				}
				else {
					found = false;
					for (unsigned int i = 0; i < deliveries.size(); i++) {
						if (deliveries[i]->getClient()->getNif() == stoi(nif)) {
							found = true;
							deliveries[i]->getClient()->orderViewer();
							break;
						}
					}
					if (!found) {
						cout << endl << "Client not found. Please try again." << endl;
						continue;
					}

				}
			}
			break;




		case 5:

			for (unsigned int i = 0; i < blacklist.size(); i++) {
				cout << *blacklist[i] << endl;
			}

			break;

		default:
			cout << "Not a valid input, please try again" << endl;
			break;
		}


	}
	return 0;
}

int Base::deliveriesMenu() {
	string deliveryOption, viewDeliveryOption,nif,name;
	bool found = false;
	Restaurant r;

	while (deliveryOption != "0") {
		cout << "_______Deliveries Menu_______\n" << endl;
		cout << "1: View total delivery list \n2: View deliveries from a client\n3:View deliveries from a restaurant\n4:View deliveries from a deliverer\n\n0: Exit to main menu" << endl;
		getline(cin, deliveryOption);
		
		if ((!isNumber(deliveryOption)) || (deliveryOption != "0" && deliveryOption != "1" && deliveryOption != "2" && deliveryOption != "3" && deliveryOption != "4")) {
			cout << "Not a valid option, please try again" << endl;
			continue;
		}

		switch (stoi(deliveryOption)) {
		
		case 0:
			system("CLS");
			return 0;
		case 1:
			
			for (unsigned int i = 0; i < deliveries.size(); i++) {
				cout << *deliveries[i] << endl;
			}
			system("pause");
			system("CLS");
			break;

		case 2:
			nif = "";

			while (nif != "0") {
				cout << "Please input the nif of the client you wish to view deliveries from:(0+Enter to leave)" << endl;
				getline(cin, nif);
				while (!isNumber(nif) && nif.length() != 9 && nif != "0") {
					cout << "Invalid NIF. Please input nif in correct format: (0+Enter to leave)" << endl;
					getline(cin, nif);
				}
				if (nif == "0") {
					nif = "";
					break;
				}
				else {
					found = false;
					for (unsigned int i = 0; i < deliveries.size(); i++) {
						if (deliveries[i]->getClient()->getNif() == stoi(nif)) {
							found = true;
							deliveries[i]->getClient()->orderViewer();
							break;
						}
					}
					if (!found) {
						cout << endl << "Client not found. Please try again." << endl;
						continue;
					}

				}
			}
			break;

		case 3:
			
			while (name != "0") {

				cout << "Which restaurant do you wish to view deliveries from? (please write name - 0 to leave)" << endl;
				getline(cin, name);

				if (name == "0")break;

				for (unsigned int j = 0; j < restaurants.size(); j++) {
					if (compare_str(restaurants[j]->getName(), name)) {
						r = *restaurants[j];
						found = true;
						name = "0";
						break;
					}
				}

				if (!found) {
					cout << "Restaurant not found. Try again:" << endl;
					continue;
				}
			}

			if(found)
				for (unsigned int i = 0; i < deliveries.size(); i++) 
					if (*deliveries[i]->getRestaurant() == r) 
						cout << *deliveries[i] << endl;
				
			
			break;

		case 4:
			nif = "";

			while (nif != "0") {
				cout << "Please input the nif of the deliverer you wish to view deliveries from:(0+Enter to leave)" << endl;
				getline(cin, nif);
				while (!isNumber(nif) && nif.length() != 9 && nif != "0") {
					cout << "Invalid NIF. Please input nif in correct format: (0+Enter to leave)" << endl;
					getline(cin, nif);
				}
				if (nif == "0") {
					nif = "";
					break;
				}
				else {
					found = false;
					for (unsigned int i = 0; i < employees.size(); i++) {
						if (employees[i]->getNif() == stoi(nif) &&employees[i]->isDeliverer()) {
							found = true;
							for (unsigned int j = 0; j < employees[i]->getHistory().size(); j++) {
								cout << *employees[i]->getHistory()[j] << endl;
							}
							break;
						}
					}
					if (!found) {
						cout << endl << "Employee not found or not a Deliverer. Please try again." << endl;
						continue;
					}

				}
			}
			break;


			break;
		default:
			cout << "Input not valid, please try again" << endl;
			break;
		}

	}
	return 0;


}

int Base::deliverersMenu(Employee *e) {

	string option;

	while (option != "0") {

		cout << "________Deliverer Menu________" << endl;
		cout << "1: View Past Deliveries\n2: View overall rating\n3: View salary\n\n0:Go Back" << endl;
		getline(cin, option);

		if ((!isNumber(option)) || (option != "0" && option != "1" && option != "2" && option != "3")) {
			cout << "Not a valid option, please try again" << endl;
			continue;
		}

		switch (stoi(option)) {
		case 1:
			for (unsigned int i = 0; i < e->getHistory().size(); i++) {
				cout << e->getHistory()[i];
			}
			system("pause");
			system("CLS");
			break;

		case 2:
			cout << endl << "Overall Rating: " << e->getMedRating() << endl << endl;
			break;

		case 3:
			cout << endl << "Salary: " << e->getSalary() << endl << endl;
			break;

		case 0:
			system("CLS");
			return 0;
		}
	}
	return 0;
}

int Base::mainMenuAdmins(Employee *e){
	
	string a[40];
	a[0] = 186; //║
	a[1] = 187; //╗
	a[2] = 188; //╝
	a[3] = 200; //╚
	a[4] = 201; //╔
	a[5] = 205; //═
	a[6] = 206; //╬
	a[7] = 204; //╠
	a[8] = 203; //╦
	a[9] = 202; //╩
	a[10] = 177;//▒
	a[11] = 176;//░
	a[12] = 178;//▓
	bool stay = true;
	while (stay) {
		system("cls");
		cout << a[4];
		for (auto i = 0; i < 72; i++)cout << a[5];
		cout << a[1];
		for (auto i = 0; i < 2; i++)cout << endl << a[0] << setw(73) << a[0];
		cout << endl << a[0] << setw(41) << "Admin Menu" << setw(32) << a[0];

		for (auto i = 0; i < 3; i++)cout << endl << a[0] << setw(73) << a[0];
		cout << endl << a[0] << setw(24) << "1) Restaurant Menu" << setw(49) << a[0];
		cout << endl << a[0] << setw(20) << "2) Client Menu" << setw(53) << a[0];
		cout << endl << a[0] << setw(22) << "3) Employee Menu" << setw(51) << a[0];
		cout << endl << a[0] << setw(24) << "4) Deliveries Menu" << setw(49) << a[0];
		cout << endl << a[0] << setw(25) << "5) Maintenance Menu" << setw(48) << a[0];
		cout << endl << a[0] << setw(20) << "6) See Profits" << setw(53) << a[0];
		for (auto i = 0; i < 2; i++)cout << endl << a[0] << setw(73) << a[0];
		cout << endl << a[0] << setw(13) << "0) Exit" << setw(60) << a[0];
		for (auto i = 0; i < 3; i++)cout << endl << a[0] << setw(73) << a[0];
		cout << endl;
		cout << a[3];
		for (auto i = 0; i < 72; i++)cout << a[5];
		cout << a[2] << endl << endl;
		string temp;
		cout << "Input the option: ";
		getline(cin, temp);
		trim(temp);
		while (!isNumber(temp) || mstoi(temp) < 0 || mstoi(temp) > 5) {
			cout << endl << "Invalid option please enter again: ";
			getline(cin, temp);
		}

		switch (mstoi(temp)) {
		case 0:
			cout << endl << "Exiting Menu" << endl;
			Sleep(1000);
			return 0;
		case 1:

			if (compare_str(e->getAJob(), "Restaurant Manager") || compare_str(e->getAJob(), "Boss")) {
				restaurantMenu();
				break;
			}
			else {
				
				cout << endl << "Not enough permissions, reloading menu";
				Sleep(2000);
				break;
			}
		case 2:
			if (compare_str(e->getAJob(), "Client Manager") || compare_str(e->getAJob(), "Boss")) {
				clientMenu();
				break;
			}
			else {
				cout << endl << "Not enough permissions, reloading menu";
				Sleep(2000);
				break;
			}
		case 3:
			if (compare_str(e->getAJob(), "Boss")) {
				employeeMenu(e);
				break;
			}
			else {

				cout << endl << "Not enough permissions, reloading menu";
				Sleep(2000);
				break;
			}
		case 4:
			deliverersMenu(e);
			break;

		case 5:
			if (compare_str(e->getAJob(), "Maintenance Manager") || compare_str(e->getAJob(), "Boss")) {
				maintenanceMenu();
				break;
			}
			else {
				cout << endl << "Not enough permissions, reloading menu";
				Sleep(2000);
				break;
			}

		case 6:
			profitMenu();
			break;
		}
		

	}

	return 0;
}


int Base::profitMenu() {
	

	string a[40];
	a[0] = 186; //║
	a[1] = 187; //╗
	a[2] = 188; //╝
	a[3] = 200; //╚
	a[4] = 201; //╔
	a[5] = 205; //═
	a[6] = 206; //╬
	a[7] = 204; //╠
	a[8] = 203; //╦
	a[9] = 202; //╩
	a[10] = 177;//▒
	a[11] = 176;//░
	a[12] = 178;//▓
	bool stay = true;
	while (stay) {
		system("cls");
		cout << a[4];
		for (auto i = 0; i < 72; i++)cout << a[5];
		cout << a[1];
		for (auto i = 0; i < 2; i++)cout << endl << a[0] << setw(73) << a[0];
		cout << endl << a[0] << setw(41) << "Profit Menu" << setw(32) << a[0];

		for (auto i = 0; i < 3; i++)cout << endl << a[0] << setw(73) << a[0];
		cout << endl << a[0] << "1) Base Profit" << setw(59) << a[0];
		cout << endl << a[0] << "2) Profit per employee" << setw(51) << a[0];
		cout << endl << a[0] << "3) Profit per restaurant" << setw(49) << a[0];
		for (auto i = 0; i < 2; i++)cout << endl << a[0] << setw(73) << a[0];
		cout << endl << a[0] << setw(13) << "0) Exit" << setw(60) << a[0];
		for (auto i = 0; i < 3; i++)cout << endl << a[0] << setw(73) << a[0];
		cout << endl;
		cout << a[3];
		for (auto i = 0; i < 72; i++)cout << a[5];
		cout << a[2] << endl << endl;
		string temp;
		cout << "Input the option: ";
		getline(cin, temp);
		trim(temp);
		while (!isNumber(temp) || mstoi(temp) < 0 || mstoi(temp) > 3) {
			cout << endl << "Invalid option please enter again: ";
			getline(cin, temp);
		}
		string datecheck;
		string nif;
		vector<string>part;
		bool skip = false;
		switch (mstoi(temp)) {
		case 0:
			cout << endl << "Exiting Menu";
			Sleep(1000);
			return 0;
		case 1:
			system("cls");
			cout << "Base profit"<<endl<<endl<<endl;
			cout << "Please enter a date interval to see the profit (DD/MM/YYYY-DD/MM/YYYY) or type all to see global profit" << endl;
			cout << "->";
			getline(cin, datecheck);
			trim(datecheck);
			if (compare_str(datecheck, "all")) {
				cout << "Total Profit: " << moneyMade(new Date(), new Date("31/12/2050"))<<endl;
				system("pause");
				break;
			}
			part = decompose(datecheck, '-');
			
			while ((part.size() != 2) && !isDateFormat(part[0]) && !isDateFormat(part[2]) && !isDateValid(new Date(part[0]), new Date(part[1]))) {
				cout << "Invalid Date please enter the int the format (DD/MM/YYYY-DD/MM/YYYY) or enter 0 to leave: " << endl;
				cout << "->";
				getline(cin, datecheck);
				trim(datecheck);
				if (datecheck == "0") {
					skip = true;
					break;
				}
				part = decompose(datecheck, '-');
			}
			if (skip) {
				skip = false;
				break;
			}
			cout << "Profit between " << Date(part[0]) << " and " << Date(part[1]) << ": "<< profitMade(new Date(part[0]), new Date(part[1]))<<endl;
			system("pause");


			break;
		case 2:
			system("cls");
			for (auto b : employees) {
				if (b->isDeliverer()) {
					cout << b->printSimplified() << endl;
				}
			}
			cout << "Type the nif of the employee you want to see";
			getline(cin,nif);
			trim(nif);
			while (!isNumber(nif) || nif.length() != 9) {
				cout << "Not a valid nif, please type again (or 0 to exit): ";
				getline(cin, nif);
				trim(nif);
				if (nif == "0") {
					skip = true;
					break;
				}
			}
			if (skip) {
				skip = false;
				break;
			}
			for (auto a : employees) {
				if (a->getNif() == mstoi(nif)) {
					cout << a->printSimplified()<<endl;
					cout << "Please enter a date interval to see the profit (DD/MM/YYYY-DD/MM/YYYY) (0 to cancel)" << endl;
					cout << "->";
					getline(cin, datecheck);
					trim(datecheck);
					if (compare_str(datecheck, "0")) {
						skip = true;
						break;
					}
					
					part = decompose(datecheck, '-');

					while ((part.size() != 2) && !isDateFormat(part[0]) && !isDateFormat(part[2]) && !isDateValid(new Date(part[0]), new Date(part[1]))) {
						cout << "Invalid Date please enter the int the format (DD/MM/YYYY-DD/MM/YYYY) or enter 0 to leave: " << endl;
						cout << "->";
						getline(cin, datecheck);
						trim(datecheck);
						if (datecheck == "0") {
							skip = true;
							break;
						}
						part = decompose(datecheck, '-');
					}
					if (skip) {
						skip = false;
						break;
					}
					cout << "Profit between " << Date(part[0]) << " and " << Date(part[1]) << ": " << a->moneyMade(new Date(part[0]), new Date(part[1]))<<endl;
					system("pause");
				}
				
			}


			break;
		case 3:
			system("cls");
			for (auto a : restaurants) {
				cout << a->printSimplified() << endl;
			}
			cout << "Type the name of the restaurant you want to see";
			getline(cin, nif);
			trim(nif);
			while (!isWord(nif)) {
				cout << "Not a valid name, please type again (or 0 to exit): ";
				getline(cin, nif);
				trim(nif);
				if (nif == "0") {
					skip = true;
					break;
				}
			}
			if (skip) {
				skip = false;
				break;
			}
			for (auto a : restaurants) {
				if (compare_str(a->getName(),nif)) {
					cout << a->printSimplified() << endl;
					cout << "Please enter a date interval to see the profit (DD/MM/YYYY-DD/MM/YYYY) (0 to cancel)" << endl;
					cout << "->";
					getline(cin, datecheck);
					trim(datecheck);
					if (compare_str(datecheck, "0")) {
						skip = true;
						break;
					}

					part = decompose(datecheck, '-');

					while ((part.size() != 2) && !isDateFormat(part[0]) && !isDateFormat(part[2]) && !isDateValid(new Date(part[0]), new Date(part[1]))) {
						cout << "Invalid Date please enter the int the format (DD/MM/YYYY-DD/MM/YYYY) or enter 0 to leave: " << endl;
						cout << "->";
						getline(cin, datecheck);
						trim(datecheck);
						if (datecheck == "0") {
							skip = true;
							break;
						}
						part = decompose(datecheck, '-');
					}
					if (skip) {
						skip = false;
						break;
					}
					cout << "Profit between " << Date(part[0]) << " and " << Date(part[1]) << ": " << moneyMade(new Date(part[0]), new Date(part[1]), a) << endl;
					system("pause");
				}

			}

			break;
		}

	}


		return 0;
}


int Base::maintenanceMenu() {

	system("cls");
	int counter = 0;
	string option = "", caroption, nummain;
	priority_queue<Tech> var;
	bool found = false;
	Tech t("n");
	Date today = currentTimeNDate().second;
	while (option != "0") {
		cout << "________Maintenance Menu________" << endl << endl;

		cout << "Needs Maintenance:" << endl;

		counter = 0;

		for (auto i : vehicles) {
			counter++;
			Date mnt = i->getLastMain().second;
			//if ((i->getLastMain().second.getYear() == currentTimeNDate().second.getYear() && currentTimeNDate().second.getMonth() - i->getLastMain().second.getMonth() >= 6) || (i->getLastMain().second.getYear() != currentTimeNDate().second.getYear() && currentTimeNDate().second.getYear() - i->getLastMain().second.getYear() == 1 && currentTimeNDate().second.getMonth() + 6 - 12 < i->getLastMain().second.getMonth()) || currentTimeNDate().second.getYear() - i->getLastMain().second.getYear() > 1) {
			if (mnt + Date(0, 6, 0) < today) {
				cout << counter << " - " << i->getBrand() << ", " << i->getModel() << ", Aquired in: " << *i->getAquisition() << endl;
			}
		}

		cout << endl << endl << "Options: " << endl;
		cout << "1 - Assign Car to Technitian for maintenance" << endl << "2 - See vehicles by least used" << endl << "3 - See vehicles by most used" << endl << "0 - Exit Menu" << endl << endl;
		getline(cin, option);

		while (!isNumber(option) || mstoi(option) > 3 || mstoi(option) < 0) {
			cout << "Option not valid. Please try again." << endl;
			getline(cin, option);
		}

		switch (stoi(option)) {
		case 1:

			cout << endl << "Which car do you wish to assign? ('-1'+Enter to leave)" << endl;
			getline(cin, caroption);

			while (mstoi(caroption) <= -1 || mstoi(caroption) > vehicles.size() || !isNumber(caroption)) {
				if (mstoi(caroption) == -1)break;

				cout << "Not a valid option. Please try again. ('-1'+Enter to leave)" << endl;
				getline(cin, caroption);

			}

			if (mstoi(caroption) == -1)break;

			

			while (!found) {

				cout << "Car to assign:  " << vehicles[mstoi(caroption) - 1]->getBrand() << ", " << vehicles[mstoi(caroption) - 1]->getModel() << endl << endl;
				cout << "How many maintenances must the technitian have completed to be selected to maintain this car? ('-1'+Enter to leave)" << endl;
				getline(cin, nummain);

				while (mstoi(nummain) <= -1 || !isNumber(nummain)) {
					if (mstoi(nummain) == -1) break;

					cout << endl << "Invalid option. Please try again. ('-1'+Enter to leave)" << endl;
					getline(cin, nummain);
				}
				if (mstoi(nummain) == -1) break;

				while (!techies.empty()) {
					//cout << techies.top().getName() << endl;

					if (techies.top().getManu() >= mstoi(nummain) && !found && compareTime(techies.top().getAvai(), currentTimeNDate())) {

						//cout << setw(2) << setfill('0') << techies.top().getAvai().first.hour << ":" << setw(2) << setfill('0') << techies.top().getAvai().first.min << "-" << techies.top().getAvai().second << endl << endl;

						cout << "The assigned technitian is " << techies.top().getName() << ". Maintenance is scheduled." << endl << endl;
						system("pause");
						t = techies.top();
						techies.pop();
						t.addManu();
						vehicles[mstoi(caroption) - 1]->setLastMain(currentTimeNDate());
						vehicles[mstoi(caroption) - 1]->setAvailable(false);
						t=Tech(t.getName(),t.getManu(),(addTimetoTimeNDate(currentTimeNDate(), Time(4, 0))));

						//cout << setw(2) << setfill('0') << addTimetoTimeNDate(currentTimeNDate(), Time(4, 0)).first.hour << ":" << setw(2) << setfill('0') << addTimetoTimeNDate(currentTimeNDate(), Time(4, 0)).first.min << "-" << addTimetoTimeNDate(currentTimeNDate(), Time(4, 0)).second << endl << endl;

						var.push(t);
						found = true;
						continue;
					}

					var.push(techies.top());
					techies.pop();


				}

				//system("pause");
				string temp;
				while (!var.empty()) {
					if (temp == var.top().getName()) {
						var.pop();
						continue;
					}
					techies.push(var.top());
					temp = var.top().getName();
					var.pop();
				}
				system("cls");
				if (!found)cout << "No such employee. Please try again." << endl << endl;
			}

			found = false;
			//system("pause");

			system("cls");

			break;


		case 2:
			system("cls");
			cout << "_________Vehicles ordered by least used_________" << endl;

			printVehiclesPerLessUsage();

			system("pause");
			system("cls");
			break;
		case 3:

			system("cls");
			cout << "_________Vehicles ordered by most used_________" << endl;

			printVehiclesPerMostUsage();

			system("pause");
			system("cls");
			break;

		case 0:
			system("cls");
			return 0;
			break;
		}
	}

	return 0;
}

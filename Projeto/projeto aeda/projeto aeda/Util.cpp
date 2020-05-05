#include "Util.h"
#include "Extra_functions.h"
#include "Clients.h"
#include "Employees.h"


using namespace std;

Delivery::Delivery() : id(0), date(new Date()), deliverer(new Deliverer()), client(new Client()), restaurant(new Restaurant()), price(0), ok(true), rated(true), rating(0), occurrence("") {
	Time t;
	t.hour = 0;
	t.hour = 0;
	this->time = t;
};

void Delivery::addProduct(pair<Product*,int> p){
	bool In = false;
	vector<pair<Product*, int>> ps = restaurant->getProdNsales();
	for (unsigned int i = 0; i < ps.size();i++) {
		if (*ps.at(i).first == *p.first) {
			ps.at(i).second += p.second;
			for (unsigned int i = 0; i < products.size(); i++) {
				if (*products[i].first == *p.first) {
					products[i].second+=p.second;
					In = true;
					break;
				}
				
			}
			if(!In) products.push_back(p);

			calculatePrice();
			restaurant->setProdNsales(ps);
			return;
		}
	}
	throw RestaurantHasNoSuchProduct(p.first); 

	
}

void Delivery::calculatePrice(){
	float result = 0.0;

	if (client->getAddress()->getMunicipality() == restaurant->getAddress()->getMunicipality()) result += 3;
	else result += 5;

	for (auto a:products) 
		result += a.first->getPrice()*a.second;
	

	if (!products.size())  throw ThereAreNoProducts(); 

	this->price = result;

}

ostream& operator<<(ostream& out, Delivery& d) {
	out << "Ordered by " << d.getClient()->getName() << endl;
	out << "Delivered by " << d.getDeliverer()->getName() << endl;
	out << "Delivered at " << setw(2) << setfill('0') << d.getTime().hour << ":" << setw(2) << setfill('0') << d.getTime().min << "-" << *d.getDate() << endl;
	out << "Ordered from " << d.getRestaurant()->getName() << endl;
	out << "Order: ";
	for (unsigned int i = 0; i < d.getProducts().size(); i++) {
		if (i != d.getProducts().size()) out << d.getProducts()[i].first->getName() << " x" << d.getProducts()[i].second << ", "; //name or name/type/price???
		else out << d.getProducts()[i].first->getName() << " x" << d.getProducts()[i].second << endl;
	}
	out << "Total price: " << d.getPrice() << endl;
	if (d.getOk()) {
		out << "State: Delivered" << endl;
		out << "Comments: " << d.getOccurrence() << endl;
	}
	else {
		out << "State: Failed" << endl;
		out << "Resaon: " << d.getOccurrence() << endl;
	}
	return out;
}

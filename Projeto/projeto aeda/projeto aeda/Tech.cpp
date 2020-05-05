#include "Tech.h"
#include "Extra_functions.h"

using namespace std;

bool Tech:: operator< ( Tech T)const {
	const pair<Time, Date> d = T.getAvai();
	const pair<Time, Date> d1 = avai;
	const int m = T.getManu();
	const int m1 = manu;
	
	if (compareTime(d1, d))return true;

	if (compareTime(d, d1))return false;

	return (m1 < m);

	
}

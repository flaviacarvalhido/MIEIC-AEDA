
#include "Extra_functions.h"
#include "Address.h"
#include "Date.h"
#include "Util.h"
#include "Clients.h"
#include "conio.h"
#include <ctime>



using namespace std;


void trimLeft(string &s) {
	s.erase(0, s.find_first_not_of(" "));
} 
void trimRight(string &s) {
	s.erase(s.find_last_not_of(" ") + 1, s.length());
}
void trim(string &s) {
	trimLeft(s);
	trimRight(s);
}
vector<string> decompose(string s, char sep) {
	vector<string> elements;
	string usage = "";
	for (unsigned int i = 0; i < s.length(); i++) {
		if (s[i] == sep) {
			trim(usage);
			replaceAccent(usage);
			elements.push_back(usage);
			usage = "";
		}
		else {
			usage += s[i];
			
			if (i == s.length() - 1) {
				trim(usage);
				elements.push_back(usage);
			}

		}
	}
	return elements;
}
bool compare_str(string str1, string str2) {
	replaceAccent(str1);
	replaceAccent(str2);

	transform(str1.begin(), str1.end(), str1.begin(), ::toupper);
	transform(str2.begin(), str2.end(), str2.begin(), ::toupper);
	if (str1 == str2) return true;
	return false;
}
bool checkDate(Date* date) {
	int d = date->getDay();
	int m = date->getMonth();
	int y = date->getYear();
	if (d > 31 || d < 1)return false;
	if (m > 12 || m < 1)return false;
	//if (y < 2019)return false;
	if (d > 29 && m == 2)return false;
	if (d > 28 && m == 2 && (y - 2000) % 4 == 0) return false;
	if (d > 30 && (((m % 2 == 0) && m < 7) || (m % 2 != 0 && m > 8)))return false;
	return true;
}
bool isDateValid(Date* begin, Date* end) {
	if (!checkDate(begin))return false;
	if (!checkDate(end))return false;

	if (end<begin) return false;
	
	return true;
}

bool isWord(string str) {
	for (unsigned int i = 0; i < str.length(); i++) {
		if (str[i] == ' ' || str[i] == 'é' || str[i] == 'É' || str[i] == 'á' || str[i] == 'à' || str[i] == 'Á' || str[i] == 'À' || str[i] == 'ó' || str[i] == 'Ó' || str[i] == 'Ã' || str[i] == 'ã' || str[i] == 'â' || str[i] == 'Â' || str[i] == 'Í' || str[i] == 'í' || str[i] == 'ê' || str[i] == 'Ê' || str[i] == 'ñ' || str[i] == 'Ñ' || str[i] == 'ú' || str[i] == 'Ú' || str[i] == 'ù' || str[i] == 'Ù' || str[i] == 'ô' || str[i] == 'Ô' || str[i] == 'ì' || str[i] == 'Ì' || str[i] == 'î' || str[i] == 'Î' || str[i] == 'õ' || str[i] == 'Õ' || str[i] == 'ü' || str[i] == 'Ü' || str[i] == 'ö' || str[i] == 'Ö')continue;
		else if (!isalpha(str[i]))return false;
	}
	return true;
}
bool isNumber(string str) {
	for (unsigned int i = 0; i < str.length(); i++) {
		
		if (str[i] == '0' || str[i] == '1' || str[i] == '2' || str[i] == '3' || str[i] == '4' || str[i] == '5' || str[i] == '6' || str[i] == '7' || str[i] == '8' || str[i] == '9'|| str[i]=='-') continue;
		else return false;
	}
	return true;


}

bool isNif(string s) {
	trim(s);
	if (s.length() != 9)
		return false;
	if (s[0] != '1' && s[0] != '2')
		return false;


	return isNumber(s);
}

bool isStreet(string str) {
	for (unsigned int i = 0; i < str.length(); i++) {
		if (str[i] == '_'  || str[i] == '*' || str[i] == '/' || str[i] == '|' || str[i] == '@' || str[i] == '(' || str[i] == ')' || str[i] == '[' || str[i] == ']' || str[i] == '{' || str[i] == '}' || str[i] == '&' || str[i] == '%' || str[i] == '$' || str[i] == '#' || str[i] == '!' || str[i] == '?' || str[i] == '§' || str[i] == '£' || str[i] == '>' || str[i] == '<') return false;
	}
	return true;
}
bool isStringIn(string str, vector<string> vec_str) {
	string check;
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	for (unsigned int i = 0; i < vec_str.size(); i++) {
		check = vec_str.at(i);
		transform(check.begin(), check.end(), check.begin(), ::toupper);
		trim(str);
		trim(check);
		if (str == check)
			return true;
	}

	return false;
}
bool isdigitm(char a) {
	if (a == '0' || a == '1' || a == '2' || a == '3' || a == '4' || a == '5' || a == '6' || a == '7' || a == '8' || a == '9') return true;
	else return false;
}
bool isDateFormat(string str) {
	trim(str);
	for (unsigned int i = 0; i < str.length(); i++) {
		if (!isdigitm(str[i]) && i != 2 && i != 5)return false;

		if ((i == 2 || i == 5) && str[i] != '/') return false;

	}
	return true;
}
void replaceAccent(string &str) {
	/*
	string result = "";
	for (unsigned int i = 0; i < str.length(); i++) {
		if (str[i] == 'á') result += 160;
		else if (str[i] == 'à') result += 133;
		else if (str[i] == 'ã')result += 198;
		else if (str[i] == 'â')result += 131;
		else if (str[i] == 'ä')result += 132;
		else if (str[i] == 'Á')result += 181;
		else if (str[i] == 'À')result += 183;
		else if (str[i] == 'Ã')result += 199;
		else if (str[i] == 'Â')result += 143;
		else if (str[i] == 'Ä')result += 142;
		else if (str[i] == 'é')result += 130;
		else if (str[i] == 'è')result += 138;
		else if (str[i] == 'ê')result += 136;
		else if (str[i] == 'ë')result += 137;
		else if (str[i] == 'É')result += 144;
		else if (str[i] == 'È')result += 212;
		else if (str[i] == 'Ê')result += 210;
		else if (str[i] == 'Ë')result += 211;
		else if (str[i] == 'ó')result += 162;
		else if (str[i] == 'ò')result += 149;
		else if (str[i] == 'õ')result += 228;
		else if (str[i] == 'ô')result += 147;
		else if (str[i] == 'ö')result += 148;
		else if (str[i] == 'Ó')result += 224;
		else if (str[i] == 'Ò')result += 227;
		else if (str[i] == 'Õ')result += 229;
		else if (str[i] == 'Ô')result += 226;
		else if (str[i] == 'Ö')result += 153;
		else if (str[i] == 'ú')result += 163;
		else if (str[i] == 'ù')result += 151;
		else if (str[i] == 'ü')result += 129;
		else if (str[i] == 'û')result += 150;
		else if (str[i] == 'Ú')result += 233;
		else if (str[i] == 'Ù')result += 235;
		else if (str[i] == 'Û')result += 234;
		else if (str[i] == 'Ü')result += 154;
		else if (str[i] == 'í')result += 161;
		else if (str[i] == 'ì')result += 141;
		else if (str[i] == 'î')result += 140;
		else if (str[i] == 'ï')result += 139;
		else if (str[i] == 'Í')result += 214;
		else if (str[i] == 'Ì')result += 222;
		else if (str[i] == 'Î')result += 215;
		else if (str[i] == 'Ï')result += 216;
		else if (str[i] == 'ç')result += 135;
		else if (str[i] == 'Ç')result += 128;
		else if (str[i] == 'ñ')result += 164;
		else if (str[i] == 'Ñ')result += 165;
		else if (str[i] == 'ý')result += 236;
		else if( str[i] == 'ÿ')result += 152;
		else if (str[i] == 'Ý')result += 237;
		else result += str[i];
	}
	str = result;
	*/
	string result = "";
	for (unsigned int i = 0; i < str.length(); i++) {
		if (str[i] == 'á' || str[i] == 'à' || str[i] == 'ã' || str[i] == 'â' || str[i] == 'ä')result += 'a';
		else if (str[i] == 'Á' || str[i] == 'À' || str[i] == 'Ã' || str[i] == 'Â' || str[i] == 'Ä')result += 'A';
		else if (str[i] == 'é' || str[i] == 'è' || str[i] == 'ê' || str[i] == 'ë')result += 'e';
		else if (str[i] == 'É' || str[i] == 'È' || str[i] == 'Ê' || str[i] == 'Ë')result += 'E';
		else if (str[i] == 'ó' || str[i] == 'ò' || str[i] == 'õ' || str[i] == 'ô' || str[i] == 'ö')result += 'o';
		else if (str[i] == 'Ó' || str[i] == 'Ò' || str[i] == 'Õ' || str[i] == 'Ô' || str[i] == 'Ö')result += 'O';
		else if (str[i] == 'ú' || str[i] == 'ù' || str[i] == 'ü' || str[i] == 'û')result += 'u';
		else if (str[i] == 'Ú' || str[i] == 'Ù' || str[i] == 'Û' || str[i] == 'Ü')result += 'U';
		else if (str[i] == 'í' || str[i] == 'ì' || str[i] == 'î' || str[i] == 'ï')result += 'i';
		else if (str[i] == 'Í' || str[i] == 'Ì' || str[i] == 'Î' || str[i] == 'Ï')result += 'I';
		else if (str[i] == 'ç')result += 'c';
		else if (str[i] == 'Ç')result += 'C';
		else if (str[i] == 'ñ')result += 'n';
		else if (str[i] == 'Ñ')result += 'N';
		else if (str[i] == 'ý' || str[i] == 'ÿ')result += 'y';
		else if (str[i] == 'Ý')result += 'Y';
		else result += str[i];
	}
	str = result;
}
void accentPlace(string& str) {
	/*
	string result = "";
	for (unsigned int i = 0; i < str.length(); i++) {
		if (str[i] == 160) result += 'á';
		else if (str[i] == 133)result += 'à';
		else if (str[i] == 198)result += 'ã';
		else if (str[i] == 131)result += 'â';
		else if (str[i] == 132)result += 'ä';
		else if (str[i] == 181)result += 'Á';
		else if (str[i] == 183)result += 'À';
		else if (str[i] == 199)result += 'Ã';
		else if (str[i] == 143)result += 'Â';
		else if (str[i] == 142)result += 'Ä';
		else if (str[i] == 130)result += 'é';
		else if (str[i] == 138)result += 'è';
		else if (str[i] == 136)result += 'ê';
		else if (str[i] == 137)result += 'ë';
		else if (str[i] == 144)result += 'É';
		else if (str[i] == 212)result += 'È';
		else if (str[i] == 210)result += 'Ê';
		else if (str[i] == 211)result += 'Ë';
		else if (str[i] == 162)result += 'ó';
		else if (str[i] == 149)result += 'ò';
		else if (str[i] == 228)result += 'õ';
		else if (str[i] == 147)result += 'ô';
		else if (str[i] == 148)result += 'ö';
		else if (str[i] == 224)result += 'Ó';
		else if (str[i] == 227)result += 'Ò';
		else if (str[i] == 229)result += 'Õ';
		else if (str[i] == 226)result += 'Ô';
		else if (str[i] == 153)result += 'Ö';
		else if (str[i] == 163)result += 'ú';
		else if (str[i] == 151)result += 'ù';
		else if (str[i] == 129)result += 'ü';
		else if (str[i] == 150)result += 'û';
		else if (str[i] == 233)result += 'Ú';
		else if (str[i] == 235)result += 'Ù';
		else if (str[i] == 234)result += 'Û';
		else if (str[i] == 154)result += 'Ü';
		else if (str[i] == 161)result += 'í';
		else if (str[i] == 141)result += 'ì';
		else if (str[i] == 140)result += 'î';
		else if (str[i] == 139)result += 'ï';
		else if (str[i] == 214)result += 'Í';
		else if (str[i] == 222)result += 'Ì';
		else if (str[i] == 215)result += 'Î';
		else if (str[i] == 216)result += 'Ï';
		else if (str[i] == 135)result += 'ç';
		else if (str[i] == 128)result += 'Ç';
		else if (str[i] == 164)result += 'ñ';
		else if (str[i] == 165)result += 'Ñ';
		else if (str[i] == 236)result += 'ý';
		else if (str[i] == 152)result += 'ÿ';
		else if (str[i] == 237)result += 'Ý';
		else result += str[i];
	}
	
	str = result;
	*/

}
bool isPostalCode(string str) {
	trim(str);
	if (str.length() != 8) return false;
	if (str[4] != '-') return false;
	string u;
	for (unsigned int i = 0; i < str.length(); i++) {
		u = str[i];
		if (!isNumber(u) && i != 4) return false;
	}
	return true;
}

bool isAddress(Address address) {
	if (!isStreet(address.getStreet())) return false;
	if (!isPostalCode(address.getZip())) return false;
	if (!isWord(address.getMunicipality())) return false;


	return true;
}

bool isFloat(string str) {
	for (unsigned int i = 0; i < str.length(); i++) {
		if (str[i] == ' ' || str[i] == 'é' || str[i] == 'É' || str[i] == 'á' || str[i] == 'à' || str[i] == 'Á' || str[i] == 'À' || str[i] == 'ó' || str[i] == 'Ó' || str[i] == 'Ã' || str[i] == 'ã' || str[i] == 'â' || str[i] == 'Â' || str[i] == 'Í' || str[i] == 'í' || str[i] == 'ê' || str[i] == 'Ê' || str[i] == 'ñ' || str[i] == 'Ñ' || str[i] == 'ú' || str[i] == 'Ú' || str[i] == 'ù' || str[i] == 'Ù' || str[i] == 'ô' || str[i] == 'Ô' || str[i] == 'ì' || str[i] == 'Ì' || str[i] == 'î' || str[i] == 'Î' || str[i] == 'õ' || str[i] == 'Õ' || str[i] == 'ü' || str[i] == 'Ü' || str[i] == 'ö' || str[i] == 'Ö') return false;

		if (!isdigitm(str[i]) && str[i] != '.')return false;
	}
	return true;
}

bool isPass(string str) {
	for (unsigned int i = 0; i < str.length(); i++) {
		if (str[i] == ' ' || str[i] == 'é' || str[i] == 'É' || str[i] == 'á' || str[i] == 'à' || str[i] == 'Á' || str[i] == 'À' || str[i] == 'ó' || str[i] == 'Ó' || str[i] == 'Ã' || str[i] == 'ã' || str[i] == 'â' || str[i] == 'Â' || str[i] == 'Í' || str[i] == 'í' || str[i] == 'ê' || str[i] == 'Ê' || str[i] == 'ñ' || str[i] == 'Ñ' || str[i] == 'ú' || str[i] == 'Ú' || str[i] == 'ù' || str[i] == 'Ù' || str[i] == 'ô' || str[i] == 'Ô' || str[i] == 'ì' || str[i] == 'Ì' || str[i] == 'î' || str[i] == 'Î' || str[i] == 'õ' || str[i] == 'Õ' || str[i] == 'ü' || str[i] == 'Ü' || str[i] == 'ö' || str[i] == 'Ö') return false;
	}
	return true;
}

vector<string> joinVectors(vector<string> vec1, vector<string> vec2) {
	for (unsigned int i = 0; i < vec2.size(); i++) {
		trim(vec2[i]);
		if (!isStringIn(vec2[i], vec1))vec1.push_back(vec2[i]);
	}
	return vec1;
}
int monthsPassed(Date* beg, Date* end) {
	if (!isDateValid(beg,end)) throw InvalidDates(beg, end);
	int result = 0;
	result += (end->getYear() - beg->getYear()) * 12;
	if (end->getMonth() < beg->getMonth()) result -= beg->getMonth() - end->getMonth();
	else result += end->getMonth() - beg->getMonth();
	return result;
}

int s1(string m) {
	if (m == "0") return 0;
	if (m == "1") return 1;
	if (m == "2") return 2;
	if (m == "3") return 3;
	if (m == "4") return 4;
	if (m == "5") return 5;
	if (m == "6") return 6;
	if (m == "7") return 7;
	if (m == "8") return 8;
	if (m == "9") return 9;
	return 0;
}


int base10(unsigned int times) {
	int result = 1;
	for (unsigned int i = 0; i < times; i++) {
		result *= 10;
	}
	return result;
}

int mstoi(string m) {
	int result = 0;
	trim(m);
	int counter = m.length();
	//cout << "length-"<<counter;
	//cout << "input-" << m;
	string usage;
	bool neg = false;
	for (unsigned int i = 0; i < m.size(); i++) {
		usage = m[i];
		if (usage == "-") {
			neg = true;
			continue;
		}
		//cout << "(" << m[i] << ")";
		result += s1(usage) * base10(counter-1);
		//cout <<"("<< result<<")";
		counter--;
	}
	if (neg)
		result *= -1;
	//cout << result;
	return result;
}


pair<Time, Date> currentTimeNDate() {
	Time t;
	Date d;
	time_t now = time(0);
	#pragma warning(suppress : 4996)
	tm* td = gmtime(&now);

	t.min = td->tm_min;
	t.hour = td->tm_hour;
	d.setDay(td->tm_mday);
	d.setMonth(td->tm_mon + 1);
	d.setYear(1900+td->tm_year);
	// cout << td->tm_year;
	return make_pair(t, d);
}




pair<Time, Date> deliveryTime(string c, string r) {
	Time t;
	Date d;
	time_t now = time(0);
#pragma warning(suppress : 4996)
	tm* td = gmtime(&now);
	double multiplier=(rand() % 5)/10 +0.7;
	int minutes;
	int extra = 0;
	int prepmin = 8;
	if (td->tm_mday > 15 && td->tm_mon == 11) {
		multiplier += (rand() % 5) / 10 + 0.5;
		prepmin += 3;
	}
	if (td->tm_mday > 15 && td->tm_mon == 6) {
		multiplier += (rand() % 1) / 10 + 0.2;
		prepmin += 2;
	}
	if (td->tm_mday < 10) {
		multiplier += (rand() % 2) / 10 + 0.3;
		prepmin += 2;
	}
	if (td->tm_wday == 5) { 
		multiplier += (rand() % 2) / 10 + 0.2;
		prepmin += 3;
	}
	if ((td->tm_hour == 19 || td->tm_hour == 21) || (td->tm_hour == 7) || (td->tm_hour == 9)) multiplier += (rand() % 6) / 10 + 0.3;
	if (td->tm_hour == 20 || td->tm_hour == 8) multiplier += (rand() % 7) / 10 + 0.5;
	if (td->tm_hour == 12 || td->tm_hour == 13) multiplier += (rand() % 2) / 10 + 0.2;
	if (compare_str(c,r)) minutes = prepmin+round(7 * multiplier);
	else minutes = prepmin+round(15 * multiplier);
	if (td->tm_min + minutes > 59) extra = 1;
	t.min = (td->tm_min+minutes) % 60;
	t.hour = (td->tm_hour+extra) % 24;
	if (td->tm_hour + extra < 24) extra = 0;
	d.setDay(td->tm_mday+extra);
	d.setMonth(td->tm_mon + 1);
	d.setYear(1900 + td->tm_year);
	if (!checkDate(new Date(d))) {
		d.setDay(1);
		d.setMonth((td->tm_mon + 2) % 13 + (td->tm_mon + 2) / 13);
		if (td->tm_mon + 2 > 12) d.setYear(1901 + td->tm_year);

	}

	return make_pair(t,d);
}


int randomKilGenerator(string ms, string md) {
	int result = rand() % 5;
	if (compare_str(ms, md))result += rand() % 2 + 3;
	else result += rand() % 6 + 7;
	return result;
}





void printHB() {
	std::cout << R"(
	,-.
	| |
	| "--.  ,--.-.,-.--. ,-.--. ,-. ,-.
	| ,-. \/ ,-. || ,-. \| ,-. \| | | |
	| | | |\ `-' || `-' /| `-' /| `-' |
	`-' `-' `--'-'| .--' | .--'  `--. |
		      | |    | |        | |
		      `-'    `-'        `-'
,-.     _       ,-.  ,-.        ,-.
| |    (_)      | |_ | |        | |
| "--. ,-.,-.--.|  _)| "--.  ,--" | ,--.-.,-. ,-.
| ,-. \| || ,-./| |  | ,-. \/ ,-. |/ ,-. || | | |
| `-' /| || |   | |  | | | |\ `-' |\ `-' || `-' |
"-'--' `-'`-'   `-'  `-' `-' `--'-' `--'-' `--. |
					      | | 
					      `-'
)";
}
void isHappyBday(Date d) {
	pair<Time, Date>td = currentTimeNDate();
	if (td.second == d) printHB();
}


string randomMotiveGenerator() {
	vector<string> s{ "Had a car crash!","Ran out of fuel!","Client didn't pay!","Incident at Restaurant!","Products damaged!","Took way too long!","Wrong products brought!","Client not at the location!","System crashed!","Vehicle Malfunction!" };


	return s[rand() % s.size()];
}


string read_pass() {
	string pass;
	string a = "";
	int key = 0;
	int nrcouts = 0;
	bool temp = false;
#pragma warning (disable : 4996)
	do {
		if (temp) {
			temp = false;
			key--;
		}
		a += ' ';
		char b = getch();
		if (b == 8) {
			if (key > 0) {
				//cout << a[key - 1];
				//a.erase(key - 1);
				a[key - 1] = ' ';
				key--;
			}


			if (nrcouts > 0) {
				nrcouts--;
				cout << '\b' << ' ' << '\b';
			}
			temp = true;
			key++;

		}
		else {
			a[key] = b;
			cout << "*";
			nrcouts++;
			key++;
		}

	} while (a[key - 1] != '\r');
	cout << '\b' << ' ';
#pragma warning (enable : 4996)
	int count = 0;
	for (auto b : a)if (b != '\r' && b != ' ')count++;
	a.erase(count, a.size() - count);
	//cout << count;
	//cout << a;
	pass = a;
	a = "";
	key = 0;
	nrcouts = 0;
	count = 0;
	trim(pass);
	return pass;
}

Date correctDate(Date date) {
	int d = date.getDay();
	int m = date.getMonth();
	int y = date.getYear();
	if (d > 28 && m == 2 && (y - 2000) % 4 == 0) { 
		d -= 28;
		m += 1;
	}
	else if (d > 29 && m == 2) {
		d -= 29;
		m += 1;
	}
	
	else if (d > 30 && (((m % 2 == 0) && m < 7) || (m % 2 != 0 && m > 8))) {
		d -= 30;
		m += 1;
	}
	else if (d > 31) {
		d -= 31;
		m += 1;
	}
	if (m > 12) {
		m -= 12;
		y += 1;
	}
	return Date(d, m, y);
}

bool compareTime(pair<Time, Date> T1, pair<Time, Date> T2) {
	Date d1 = T1.second;
	Date d2 = T2.second;
	Time t1 = T1.first;
	Time t2 = T2.first;
	if (d1 < d2)return true;
	if (d2 < d1)return false;
	
	return t1<t2;
}


pair<Time, Date> readDateNTime(string s) {
	vector<string>parts = decompose(s, '-');
	return make_pair(Time(parts.at(0)), Date(parts.at(1)));
}


pair<Time, Date> addTimetoTimeNDate(pair<Time, Date> td, Time t1) {

	Time temp = td.first;
	td.first = td.first + t1;
	if (td.first < temp) td.second = td.second + 1;

	return td;

}

string printTimeNDate(pair<Time, Date> t) {
	stringstream s;
	s << t.first.hour << ":" << t.first.min << "-" << t.second;
	return s.str();
}

int sumNif(int nif) {
	string s = to_string(nif);
	int result = 0;
	string usage;
	for (unsigned i = 0; i < s.size(); i++) {
		usage = s[i];
		result += s1(usage);
	}
	return result;
}

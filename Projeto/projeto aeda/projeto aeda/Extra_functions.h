#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <sstream>
#include <cmath>
#include "Date.h"
#include "Address.h"



using namespace std;
/**
*@brief removes the spaces at the left of the string
*@param s - string being changed
*/
void trimLeft(string &s);
/**
*@brief removes the spaces at the right of the string
*@param s - string being changed
*/
void trimRight(string &s);
/**
*@brief removes the spaces at both sides of the string
*@param s - string being changed
*/
void trim(string &s);
/**
*@brief decomposes a string in smaller string separated by a char
*@param s - string being changed
*@param sep - char that separates the smaller strings
*@return vector of strings that were separated by the char
*/
vector<string> decompose(string s, char sep);
/**
*@brief checks if the strings have the same character by turning both of them to uppercase
*@param str1 - string being commpared
*@param str2 - other string being commpared
*@return true if the strings have the same characters
*/
bool compare_str(string str1, string str2);
/**
*@brief calculates the number of months passed between the given dates
*@param beg - beggining date
*@param end - end date
*@return number of months passed
*/
int monthsPassed(Date* beg, Date* end);
/**
*@brief checks if the date is valid (even checks the leap years)
*@param date - date being checked
*@return true if the date is valid
*/
bool checkDate(Date* date);
/**
*@brief checks if the end date isnt bigger than the beggining and if both dates are valid
*@param beg - beggining date
*@param end - end date
*@return true if the dates are valid, false otherwise
*/
bool isDateValid(Date* begin, Date* end);
/**
*@brief checks if the string is in the vector by changing the string and each element of the vector to uppercase
*@param str - string being checked
*@param vec_str - vector being checked of having the string
*@return true if the string is in the vector, false otherwise
*/
bool isStringIn(string str, vector<string> vec_str);
/**
*@brief my version of isdigit that doesnt crash if the char is an extended ascii 
*@param a - char being checked of being a digit
*@return true if thee char is a digit
*/
bool isdigitm(char a);
/**
*@brief checks if the string as the format to be a date
*@param str - string being checked
*@return true if the string as a date format, false otherwise
*/
bool isDateFormat(string str);
/**
*@brief it is supposed to replace accents with the ascii code so it could be printed but it still deformates so it was changed to removing the accents
*@param str - string changed
*/
void replaceAccent(string& str);
/**
*@brief it is supposed to replace the ascii code  with  accents it coreresponds to so it could be written in the file but it still deformates so it was commented
*@param str - string changed
*/
void accentPlace(string& str);
/**
*@brief checks if the address as the correct parameters
*@param address - adress being checked
*@return true if the address is correct, false otherwise
*/
bool isAddress(Address address);/**
*@brief checks if the string is a float
*@param str - string being checked
*@return true if the string is a float, false otherwise
*/
bool isFloat(string str);
/**
*@brief checks if the string is a password
*@param str - string being checked
*@return true if the string is a password, false otherwise
*/
bool isPass(string str);
/**
*@brief checks if the string is a number (int)
*@param str - string being checked
*@return true if the string is a number (int), false otherwise
*/
bool isNumber(string str);


bool isNif(string s);
/**
*@brief checks if the string is a word
*@param str - string being checked
*@return true if the string is a word, false otherwise
*/
bool isWord(string str);
/**
*@brief checks if the string is a street
*@param str - string being checked
*@return true if the string is a street, false otherwise
*/
bool isStreet(string str);
/**
*@brief checks if the string is a zip (ignore it being called postalcode)
*@param str - string being checked
*@return true if the string is a zip, false otherwise
*/
bool isPostalCode(string str);
vector<string> joinVectors(vector<string> vec1, vector<string> vec2);
/**
*@brief a version of pow() that doesn't return a double
*@param times - number of times 10 is being multiplied
*@return the result of pow(10,times)
*/
int base10(unsigned int times);
/**
*@brief my version of stoi because i was having trouble with it
*@param m - string being transformed
*@return the resulting number
*/
int mstoi(string m);
/**
*@brief reads the current time and date
*@return returns the current time and date
*/
pair<Time, Date> currentTimeNDate();
/**
*@brief reads the current time and date and calculates a delivery time based on some factors (time of the year, starting of the month, time of the day) and some luck
*@return returns the delivery arriving time that was generated
*/
pair<Time, Date> deliveryTime(string c, string r);
/**
*@brief prints happy birthday in ascii art
*/
void printHB();
/**
*@brief checks if the date is today, if so prints happy birthday in ascii art
*@param d - date being checked
*/
void isHappyBday(Date d);
/**
*@brief randomly generates a motive from a defined list for the delivery going wrong  
*@return a string with the random motive
*/
string randomMotiveGenerator();



string read_pass();


pair<Time, Date> readDateNTime(string s);



int randomKilGenerator(string ms, string md);


Date correctDate(Date date);


pair<Time, Date> addTimetoTimeNDate(pair<Time, Date> td, Time t1);

string printTimeNDate(pair<Time, Date> t);

int sumNif(int nif);

bool compareTime(pair<Time, Date> T1, pair<Time, Date> T2);

/**
*@brief binary search with a small alteration due to my vectors being sorted differently
*@param x - generic element of class T being searched
*@param v - generic vector of class T we are searching in
*@return the postion of the element in the vector, if not found returns -1
*/
template <class T>
int search(T* x, vector<T*> v) { //had to change the binary search bc the wait the vector is sorted is opposite of what the binary search wants!


	int left = 0, right = v.size() - 1;
	while (left <= right)
	{
		int middle = (left + right) / 2;
		//cout << " l:" << left;
		//cout << " r:" << right;
		//cout << " m:" << middle << endl;
		if (*v[middle] > *x)
			left = middle + 1;
		else if (*x > *v[middle])
			right = middle - 1;
		else
			return middle; // found
	}

	return -1; //not found
}
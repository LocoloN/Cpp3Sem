// Proj.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <cmath>
#include <time.h>
using namespace std;


class InvalidFractionException : exception
{
private:
	 char* message;
public:
	InvalidFractionException(const char* mes)
	{
		*message = *mes;
	}
	virtual char* what()
	{
		return message;
	}
};

class SquareFraction 
{
	
private:
	int numerator;
	int denominator;
	bool IsSquare(int num)
	{
		return (pow((int)sqrt(num), 2) == num);
	}
public:
	SquareFraction(int _numerator, int _denominator)
	{
		if (!IsSquare(_numerator)) throw InvalidFractionException("the numerator is not the square of an integer");
		numerator = _numerator;
		denominator = _denominator;
	}
	double GetMeasure()
	{
		return numerator / denominator;
	}
	bool operator < (SquareFraction &obj)
	{
		double res1 = this->numerator / (double)this->denominator;
		double res2 = obj.numerator/ (double)obj.denominator;
		return (res1 < res2);
	}

	friend ostream & operator << (ostream&, const SquareFraction&);
};
	ostream & operator << (ostream &outputStream, const SquareFraction &obj)
	{
		return outputStream << obj.numerator << "/" << obj.denominator << "\n";
	}

template<typename T>
void push(T &element,list<T> &listObj)
{
	listObj.push_back(element);
}
template<typename T>
void push(T& element,typename list<T>::iterator iter, list<T>& listObj)
{
	listObj.insert(iter,element);
}
template <typename T>
list<T>& filter(list<T>& obj,bool (*P)(T))
{
	list<T> result;
	for (T elem : obj)
	{
		P(elem) ? result.push_back(elem) : void();
	}
}

template<typename T>
T pop(typename list<T>::iterator iter, list<T>& listObj)
{
	listObj.erase(iter);
	return *listObj.begin();
}
template<typename T>
void displayList(list<T> obj)
{
	for (auto iter = obj.begin(); iter != obj.end(); iter++)
	{
		cout << *iter;
	}
}

class Site
{
public:
	Site()
	{
		
	}

	bool operator < (Site obj)
	{
		return (this->dailyVisitors < obj.dailyVisitors) ||
		((this->dailyVisitors < obj.dailyVisitors) && (this->lastUpdateDate < obj.lastUpdateDate)) || 
		((this->dailyVisitors < obj.dailyVisitors) && (this->lastUpdateDate < obj.lastUpdateDate) && (this->address < obj.address));
	}
private:
	string name;
	string address;
	string launchDate;
	string language;
	string siteType;
	string cms;
	int lastUpdateDate; //Days since update
	int dailyVisitors;


};


int main()
{
	SquareFraction a(9, 5);
	SquareFraction b(9, 2);
	SquareFraction c(9, 4);
	SquareFraction d(9, 3);
	list<SquareFraction> myList{ a,b,c };

	displayList<SquareFraction>(myList);
	cout << "\n";
	push<SquareFraction>(d, myList);
	cout << "\n";

	displayList<SquareFraction>(myList);

	pop<SquareFraction>(myList.begin()++, myList);
	cout << "\n";
	cout << "\n";

	displayList<SquareFraction>(myList);

}
//Сортировка по величине дроби



/*
Antony Tejakusuma
CIS 22B
Winter 2016
Assignment  D
Problem D1
Description of problem:
Implements operator overloading into the class, in this case
the operator == is being overloaded.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

class Car
	{
	private:
		string reportingMark;
		int carNumber;
		string kind;
		bool loaded;
		string destination;
	public:
		Car(){setup("", 0, "other", false, "NONE");}
		Car(const Car &obj){setup(obj.reportingMark, obj.carNumber, obj.kind, obj.loaded, obj.destination);}
		Car(string rM, int cN, string k, bool l, string d){setup(rM, cN, k, l, d);}
		~Car(){}
		void setup(string reportingMark, int carNumber, string kind, bool loaded, string destination);
		void output();
		friend bool operator==(const Car &left, const Car &right);
	};

void input();

int main ()
	{
	input();
	}

/***************************************************
Car class functions
***************************************************/ 

/* ******************** Car::setup ********************
sets the values in the object
*/ 
void Car::setup(string rm, int cn, string k, bool l, string d)
	{
	reportingMark = rm;
	carNumber = cn;
	kind = k;
	loaded = l;
	destination = d;
	}

/* ******************** Car::output ********************
prints the member data in a neat format
*/ 
void Car::output()
	{
	cout << "Reporting Mark\t: " << reportingMark << endl;
	cout << "Car Number\t: " << carNumber << endl;
	cout << "Kind of Car\t: " << kind << endl;
	cout << "Loaded\t\t: " << boolalpha << loaded << endl;
	cout << "Destination\t: " << destination << endl << endl;
	}

/* ******************** operator== ********************
modifies/overloads the == operator to behave a certain way
*/ 
bool operator==(const Car &left, const Car &right)
	{
	bool status;
	if (left.reportingMark == right.reportingMark && left.carNumber == right.carNumber)
		status = true;
	else 
		status = false;
	return status;
	}

/***************************************************
global functions
***************************************************/

/* ******************** input ********************
Reads the reportingMark, carNumber, kind, loaded,
and destination from the user
*/ 
void input()
	{
	string reportingMark;
	int carNumber;
	string kind;
	bool loaded;
	string destination;
	string carType;

	ifstream inputFile("input.txt");
	if(inputFile.fail())
		{
		cout << "Input file failed to open." << endl;
		exit(-1);
		}
	while(inputFile.peek() != EOF)
		{	
		inputFile >> carType >> reportingMark >> carNumber >> kind >> loaded;
		getline(inputFile, destination);
		if (carType == "Car")
			{	
			Car temp(reportingMark, carNumber, kind, loaded, destination);
			temp.output();
			} else {
			cout << "NOT CAR!" << endl;
			}
		}
		
	inputFile.close();
	}



/* Execution results

*/ 


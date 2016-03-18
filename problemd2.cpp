/*
Antony Tejakusuma
CIS 22B
Winter 2016
Assignment D
Problem D2
Description of problem:
Reads a file and use the data in that file create objects
then put all object into one array.
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
		Car &operator=(const Car & carB);
	};

class StringOfCars
	{
	private:
		Car *ptr;
		static const int ARRAY_SIZE = 10;
		int carCount;
	public:
		StringOfCars()
			{
			ptr = new Car[ARRAY_SIZE];
			carCount = 0;
			}
		StringOfCars(const StringOfCars &obj)
			{
			ptr = new Car[ARRAY_SIZE];
			for(int i = 0; i > ARRAY_SIZE; i++)
				ptr[i] = obj.ptr[i];
			carCount = obj.carCount;
			}
		~StringOfCars(){delete []ptr;}
		void push(Car &obj);
		void pop(Car &obj);
		void output();
	};

void input(StringOfCars &obj);

int main ()
	{
	cout << "TEST 1" << endl;
	Car car1("SP", 34567, "business", true, "Salt Lake City");
	Car car2;
	car2 = car1;
	car2.output();

	cout << "TEST 2" << endl;
	StringOfCars string1;
	input(string1);
	cout << "STRING 1" << endl;
	string1.output();

	cout << "TEST 3" << endl;
	Car car3;
	string1.pop(car3);
	cout << "CAR 3" << endl;
	car3.output();
	cout << "STRING 1" << endl;
	string1.output();
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

/* ******************** Car::operator= ********************
sets the values in the left hand object from the right hand object
*/ 
Car & Car::operator=(const Car & carB)
  {
  setup(carB.reportingMark, carB.carNumber, carB.kind, carB.loaded, carB.destination);

  return * this;
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
StringOfCars class functions
***************************************************/ 

/* ******************** push ********************
adds a car to the string of cars
*/ 
void StringOfCars::push(Car &obj)
	{
	if(carCount < ARRAY_SIZE)
		{	
		ptr[carCount] = obj;
		carCount++;
		} else {
			cout << "StringOfCars is full!" << endl;
		}
	}

/* ******************** pop ********************
removes a car from the string of cars, Last in First Out.
*/ 
void StringOfCars::pop(Car &obj)
	{
	if(carCount > 0)
		{	
		obj = ptr[carCount - 1];
		carCount--;
		} else {
			cout << "StringOfCars is empty!" << endl;
		}
	}
/* ******************** output ********************
prints the cars inside the string of cars along with its heading.
*/ 
void StringOfCars::output()
	{
	if(carCount == 0)
		{	
		cout << "NO Cars!" << endl;
		} else {
			for(int i = 0; i < carCount; i++)
			{	
			cout << "Car Number " << i + 1 << endl;
			ptr[i].output();
			}
		}
	}
/***************************************************
global functions
***************************************************/

/* ******************** input ********************
Reads the reportingMark, carNumber, kind, loaded,
and destination from a file
*/ 
void input(StringOfCars &obj)
	{
	string reportingMark;
	int carNumber;
	string kind;
	bool loaded;
	string destination;
	string carType;

	ifstream inputFile;
	inputFile.open("input.txt");

	if(inputFile.fail())
		{
		cout << "Input file failed to open." << endl;
		exit(-1);
		}
	while(inputFile.peek() != EOF)
		{	
		inputFile >> carType;
		inputFile >> reportingMark;
		inputFile >> carNumber;
		inputFile >> kind;
		inputFile >> boolalpha >> loaded;
		while(inputFile.peek() == ' ')	
			inputFile.get();
		getline(inputFile, destination);
		if (carType == "Car")
			{	
			Car temp(reportingMark, carNumber, kind, loaded, destination);
			obj.push(temp);
			} else {
				cout << "Error: not a car!" << endl;
			}
		inputFile.clear();
		}
	inputFile.close();
	}

/* Execution results
TEST 1
Reporting Mark	: SP
Car Number		: 34567
Kind of Car		: business
Loaded			: true
Destination		: Salt Lake City

TEST 2
STRING 1
Car Number 1
Reporting Mark	: CN
Car Number		: 819481
Kind of Car		: maintenance
Loaded			: false
Destination		: NONE

Car Number 2
Reporting Mark	: SLSF
Car Number		: 46871
Kind of Car		: business
Loaded			: true
Destination		: Memphis

Car Number 3
Reporting Mark	: AOK
Car Number		: 156
Kind of Car		: tender
Loaded			: true
Destination		: McAlester

TEST 3
CAR 3
Reporting Mark	: AOK
Car Number		: 156
Kind of Car		: tender
Loaded			: true
Destination		: McAlester

STRING 1
Car Number 1
Reporting Mark	: CN
Car Number		: 819481
Kind of Car		: maintenance
Loaded			: false
Destination		: NONE

Car Number 2
Reporting Mark	: SLSF
Car Number		: 46871
Kind of Car		: business
Loaded			: true
Destination		: Memphis
*/ 


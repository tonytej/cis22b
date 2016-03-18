/*
Antony Tejakusuma
CIS 22B
Winter 2016
Assignment E
Problem E2
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
	protected:
		string reportingMark;
		int carNumber;
		string kind;
		bool loaded;
		string destination;
	public:
		Car(){setup("", 0, "other", false, "NONE");}
		Car(const Car &obj){setup(obj.reportingMark, obj.carNumber, obj.kind, obj.loaded, obj.destination);}
		Car(string rM, int cN, string k, bool l, string d){setup(rM, cN, k, l, d);}
		virtual ~Car(){}
		void setup(string reportingMark, int carNumber, string kind, bool loaded, string destination);
		void output();
		friend bool operator==(const Car &left, const Car &right);
		Car &operator=(const Car & carB);
		virtual void setKind(string kind);
	};

class FreightCar : public Car
	{
	public:
		FreightCar() : Car(){};
		FreightCar(const FreightCar &obj) : Car(obj){};
		FreightCar(string rM, int cN, string k, bool l, string d) : Car(rM, cN, k, l, d){};
		~FreightCar(){}
		FreightCar &operator=(const FreightCar & carB);
		void setKind(string kind);
	};

class PassengerCar : public Car
	{
	public:
		PassengerCar() : Car(){};
		PassengerCar(const PassengerCar &obj) : Car(obj){};
		PassengerCar(string rM, int cN, string k, bool l, string d) : Car(rM, cN, k, l, d){};
		~PassengerCar(){}
		PassengerCar &operator=(const PassengerCar & carB);
		void setKind(string kind);
	};

class StringOfCars
	{
	private:
		Car **ptr;
		static const int ARRAY_SIZE = 10;
		int carCount;
	public:
		StringOfCars()
			{
			Car *ptrToCar;
			ptr = &ptrToCar;
			ptr = new Car*[ARRAY_SIZE];
			for(int i = 0; i > ARRAY_SIZE; i++)
				{
				ptr[i] = new Car;
				ptr[i] = NULL;
				}
			carCount = 0;
			}
		StringOfCars(const StringOfCars &obj)
			{
			Car *ptrToCar;
			ptr = &ptrToCar;
			ptr = new Car*[ARRAY_SIZE];
			for(int i = 0; i > ARRAY_SIZE; i++)
				{
				ptr[i] = new Car;
				ptr[i] = NULL;
				}
			carCount = 0;
			push(*ptrToCar);
			}
		~StringOfCars()
			{
			for(int i = 0; i > ARRAY_SIZE; i++)
				delete ptr[i];
			delete []ptr;
			}
		void push(Car &obj);
		void pop(Car &obj);
		void output();
	};

void input(StringOfCars &obj);

int main ()
	{
	Car car1("SLSF", 46871, "wrecker", true, "Memphis");
	car1.output();

	FreightCar car2("MP", 98765, "gondola", true, "Saint Louis");
	car2.output();

	PassengerCar car3("PAPX", 145, "combine", true, "Tucson");
	car3.output();

	return 0;
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
	(*this).setKind(k);
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

 /* ******************** Car::setKind ********************
set the appropriate kind of car
*/ 
void Car::setKind(string k)
	{
	if (k == "business" || k == "maintenace")
		{	
		kind = k;
		} else {
			kind = "other";
		}
	}

/***************************************************
FreightCar class functions
***************************************************/ 

/* ******************** FreightCar::operator= ********************
sets the values in the left hand object from the right hand object
*/ 
FreightCar & FreightCar::operator=(const FreightCar & carB)
  	{
  	setup(carB.reportingMark, carB.carNumber, carB.kind, carB.loaded, carB.destination);
  	return * this;
  	}

 /* ******************** FreightCar::setKind ********************
set the appropriate kind of car
*/ 
void FreightCar::setKind(string k)
	{
	if (k == "box" || k == "tank" || k == "flat")
		{	
		kind = k;
		} else {
			kind = "otherFreight";
		}
	}

/***************************************************
PassengerCar class functions
***************************************************/ 

/* ******************** PassengerCar::operator= ********************
sets the values in the left hand object from the right hand object
*/ 
PassengerCar & PassengerCar::operator=(const PassengerCar & carB)
  	{
  	setup(carB.reportingMark, carB.carNumber, carB.kind, carB.loaded, carB.destination);
  	return * this;
  	}

 /* ******************** PassengerCar::setKind ********************
set the appropriate kind of car
*/ 
void PassengerCar::setKind(string k)
	{
	if (k == "chair" || k == "sleeper")
		{	
		kind = k;
		} else {
			kind = "otherPassenger";
		}
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


/* ******************** output ********************
prints the cars inside the string of cars along with its heading.
*/ 
void StringOfCars::output()
	{
	if(carCount == 0)
		{	
		cout << "NO Cars!" << endl;
		} else {
			cout << carCount << endl;
			for(int i = 0; i < carCount; i++)
				{	
				cout << "Car Number " <<  i + 1 << endl;
				ptr[i]->output();
				}
			}
	}

/* ******************** push ********************
adds a car to the string of cars
*/ 
void StringOfCars::push(Car &obj)
	{
	if(carCount < ARRAY_SIZE)
		{
		Car *ptrToCar;
		ptrToCar = new Car;
		ptrToCar = &obj;
		ptr[carCount] = ptrToCar;
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
		obj = *(ptr[carCount - 1]);
		ptr[carCount - 1] = NULL;
		carCount--;
		} else {
			cout << "StringOfCars is empty!" << endl;
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
		cout << endl << reportingMark << endl;
		if (carType == "Car")
			{	
			Car temp(reportingMark, carNumber, kind, loaded, destination);
			obj.push(temp);
			cout << endl << reportingMark <<  " pushed!" << endl;
			} else {
				cout << "Error: not a car!" << endl;
			}
		inputFile.clear();
		}
	inputFile.close();
	}

/* Execution results
Reporting Mark	: SLSF
Car Number		: 46871
Kind of Car		: other
Loaded			: true
Destination		: Memphis

Reporting Mark	: MP
Car Number		: 98765
Kind of Car		: other
Loaded			: true
Destination		: Saint Louis

Reporting Mark	: PAPX
Car Number		: 145
Kind of Car		: other
Loaded			: true
Destination		: Tucson
*/ 


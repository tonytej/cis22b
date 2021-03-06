/*
Antony Tejakusuma
CIS 22B
Winter 2016
Assignment E
Problem E3
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
		FreightCar(string rM, int cN, string k, bool l, string d){setup(rM, cN, k, l, d);}
		~FreightCar(){}
		FreightCar &operator=(const FreightCar & carB);
		void setKind(string kind);
	};

class PassengerCar : public Car
	{
	public:
		PassengerCar() : Car(){};
		PassengerCar(const PassengerCar &obj) : Car(obj){};
		PassengerCar(string rM, int cN, string k, bool l, string d){setup(rM, cN, k, l, d);}
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
			ptr = new Car*[ARRAY_SIZE];
			for(int i = 0; i > ARRAY_SIZE; i++)
				{
				ptr[i] = NULL;
				}
			carCount = 0;
			}
		StringOfCars(const StringOfCars &obj)
			{
			ptr = new Car*[ARRAY_SIZE];
			carCount = 0;
			for(int i = 0; i > ARRAY_SIZE; i++)
				{
				ptr[i] = NULL;
				push(*(obj.ptr)[i]);
				}
			}
		~StringOfCars()
			{
			for(int i = 0; i > ARRAY_SIZE; i++)
				delete ptr[i];
			delete []ptr;
			}
		void push(const Car &obj);
		void push(const FreightCar &obj);
		void push(const PassengerCar &obj);
		void pop(Car &obj);
		void output();
	};

void input(StringOfCars &obj);

int main ()
	{
	StringOfCars string1;
	input(string1);
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
	this->setKind(k);
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
	if (k == "business" || k == "maintenance")
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
			for(int i = 0; i < carCount; i++)
				{	
				cout << "Car Number " <<  i + 1 << endl;
				ptr[i]->output();
				}
			}
	}

/* ******************** push ********************
adds an object of Car type to the string of cars
*/ 
void StringOfCars::push(const Car &obj)
	{
	if(carCount < ARRAY_SIZE)
		{
		Car *ptrToCar;
		ptrToCar = new Car;
		*ptrToCar = obj;
		ptr[carCount] = ptrToCar;
		carCount++;
		} else {
			cout << "StringOfCars is full!" << endl;
		}
	}

/* ******************** push ********************
adds an object of FreightCar type to the string of cars
*/
void StringOfCars::push(const FreightCar &obj)
	{
	if(carCount < ARRAY_SIZE)
		{
		FreightCar *ptrToCar;
		ptrToCar = new FreightCar;
		*ptrToCar = obj;
		ptr[carCount] = ptrToCar;
		carCount++;
		} else {
			cout << "StringOfCars is full!" << endl;
		}
	}

/* ******************** push ********************
adds an object of PassengerCar type to the string of cars
*/ 
void StringOfCars::push(const PassengerCar &obj)
	{
	if(carCount < ARRAY_SIZE)
		{
		PassengerCar *ptrToCar;
		ptrToCar = new PassengerCar;
		*ptrToCar = obj;
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
		delete ptr[carCount - 1];
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
	string order;
	int carNumber;
	string kind;
	bool loaded;
	string destination;
	string carType;

	ifstream inputFile;
	inputFile.open("input1.txt");

	if(inputFile.fail())
		{
		cout << "Input file failed to open." << endl;
		exit(1);
		}
	while(inputFile.peek() != EOF)
		{	
		inputFile >> carType;
		inputFile >> order;
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
			} 
		else if (carType == "FreightCar")
			{
			FreightCar temp(reportingMark, carNumber, kind, loaded, destination);
			obj.push(temp);
			} 
		else if (carType == "PassengerCar")
			{	
			PassengerCar temp(reportingMark, carNumber, kind, loaded, destination);
			obj.push(temp);
			}
		else 
			{
			cout << "Error: not a car!" << endl;
			}
		inputFile.clear();
		}
	inputFile.close();
	}

/* Execution results
Car Number 1
Reporting Mark	: CN
Car Number	: 819481
Kind of Car	: maintenance
Loaded		: false
Destination	: NONE

Car Number 2
Reporting Mark	: SLSF
Car Number	: 46871
Kind of Car	: business
Loaded		: true
Destination	: Memphis

Car Number 3
Reporting Mark	: AOK
Car Number	: 156
Kind of Car	: other
Loaded		: true
Destination	: McAlester

Car Number 4
Reporting Mark	: MKT
Car Number	: 123456
Kind of Car	: tank
Loaded		: false
Destination	: Fort Worth

Car Number 5
Reporting Mark	: MP
Car Number	: 98765
Kind of Car	: box
Loaded		: true
Destination	: Saint Louis

Car Number 6
Reporting Mark	: SP
Car Number	: 567890
Kind of Car	: flat
Loaded		: true
Destination	: Chicago

Car Number 7
Reporting Mark	: GMO
Car Number	: 7878
Kind of Car	: otherFreight
Loaded		: true
Destination	: Mobile

Car Number 8
Reporting Mark	: KCS
Car Number	: 7893
Kind of Car	: chair
Loaded		: true
Destination	: Kansas City

Car Number 9
Reporting Mark	: PAPX
Car Number	: 145
Kind of Car	: sleeper
Loaded		: true
Destination	: Tucson

Car Number 10
Reporting Mark	: GN
Car Number	: 744
Kind of Car	: otherPassenger
Loaded		: false
Destination	: NONE
*/ 


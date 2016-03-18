/*
Antony Tejakusuma
CIS 22B
Winter 2016
Assignment C
Problem C3
Description of problem:
Implements operator overloading into the class, in this case
the operator == is being overloaded.
*/

#include <iostream>

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

void input(string &reportingMark, int &carNumber, string &kind, bool &loaded, string &destination);

int main ()
	{
	string reportingMark;
	int carNumber;
	string kind;
	bool loaded;
	string destination;
	input(reportingMark, carNumber, kind, loaded, destination);
	Car car1(reportingMark, carNumber, kind, loaded, destination);
	Car car2(car1);
	Car car3;
	cout << "Contents of car1:" << endl;
	car1.output();
	cout << "Contents of car2:" << endl;
	car2.output();
	cout << "Contents of car3:" << endl;
	car3.output();

	if (car1 == car2)
  		cout << "car1 is the same car as car2\n";
	else
  		cout << "car1 is not the same car as car2\n";
	if (car2 == car3)
 		cout << "car2 is the same car as car3\n";
	else
  		cout << "car2 is not the same car as car3\n";
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
void input(string &reportingMark, int &carNumber, string &kind, bool &loaded, string &destination)
	{
	cout << "Enter reporting mark: ";
	cin >> reportingMark;
	while(reportingMark.length() < 2 || reportingMark.length() > 4)
		{	
		cout << "Please enter a reporting mark with two to four characters: ";
		cin >> reportingMark;
		}
	cout << "Enter car number: ";
	cin >> carNumber;
	cout << "Enter kind of car: ";
	cin >> kind;
	while(kind != "business" && kind != "maintenance" && kind != "other")
		{	
		cout << "Please enter either business, maintenance or other: ";
		cin >> kind;
		}
	cout << "Enter whether the car is loaded (y/n): ";
	string isLoaded;
	cin >> isLoaded;
	if (isLoaded == "y")
		{
		loaded = true;
		cout << "Enter destination: ";
		cin.ignore(1000, '\n');
		getline(cin, destination);
		cout << endl;
		} else {
			loaded = false;
			string isDest;
			cout << "Do you want to enter a destination? (y/n) ";
			cin >> isDest;
		if (isDest == "y")
			{	
			cout << "Enter destination: ";
			cin.ignore(1000, '\n');
			getline(cin, destination);
			cout << endl;
			} else {
				destination = "NONE";
			}
		}
	}

/* Execution results
Enter reporting mark: SP
Enter car number: 34567
Enter kind of car: business
Enter whether the car is loaded (y/n): y
Enter destination: Salt Lake City

Contents of car1:
Reporting Mark	: SP
Car Number	: 34567
Kind of Car	: business
Loaded		: true
Destination	: Salt Lake City

Contents of car2:
Reporting Mark	: SP
Car Number	: 34567
Kind of Car	: business
Loaded		: true
Destination	: Salt Lake City

Contents of car3:
Reporting Mark	: 
Car Number	: 0
Kind of Car	: other
Loaded		: false
Destination	: NONE

car1 is the same car as car2
car2 is not the same car as car3
*/ 


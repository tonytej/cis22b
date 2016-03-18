/*
Albert Reynaldi Sudjana
Winter 2016
Assignment D
Problem D2
This program includes the creation of an array of Car objects
The Car objects will be created and obtained from a file
This program will output the data for each car
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

            //Deafult Constructor
            Car()
                {
                    setup("", 0, "other",false,"NONE");
                }

            //Copy Constructor
            Car(const Car &obj)
                {
                    setup(obj.reportingMark, obj.carNumber, obj.kind, obj.loaded, obj.destination);
                }

            //Other Constructor
            Car(string reportingM, int carN, string k, bool l, string d)
                {
                    setup(reportingM, carN, k, l, d);
                }

            //Destructor
            ~Car(){}

            /***************************************************
                Car class functions
            ***************************************************/
            void setup(string reportingM, int carN, string k, bool l, string d);

            void output();

            friend bool operator==(const Car &x, const Car &y);

            Car & operator=(const Car & carB);

    };

class StringOfCars
    {
        private :

            Car *ptr;
            static const int ARRAY_SIZE = 10;
            int carCount;

        public:

            //Deafult Constructor
            StringOfCars()
                {
                    ptr = new Car[ARRAY_SIZE];
                    carCount = 0;
                }

            //Copy Constructor
            StringOfCars(const StringOfCars &obj)
                {
                     ptr = new Car[ARRAY_SIZE];
                     carCount = obj.carCount;
                     for(int i = 0; i<ARRAY_SIZE; i++)
                        {
                            ptr[i] = obj.ptr[i];
                        }
                }
            //Destructor
            ~StringOfCars()
                {
                    delete [] ptr;
                }

            /***************************************************
                StringOfCar class functions
            ***************************************************/
            /* ******************** StringOfCars::push ********************
            Adds the Car object to the Car array
            prints error if array is full and exits
            */
            void push(Car element)
                {
                    if(carCount >= ARRAY_SIZE)
                        {
                            cout << "Error: String Of Cars is full";
                            exit(-1);
                        }
                    else
                        {
                            ptr[carCount] = element;
                            carCount++;
                        }
                }
            /* ******************** StringOfCars::pop ********************
            Last object in array is taken out and taken into the parameter
            Car object
            prints error if array empty and exits
            */
            void pop(Car &object)
                {
                    if(carCount == 0)
                        {
                            cout << "Error: String Of Cars is empty";
                            exit(-1);
                        }
                    else
                        {
                            object = ptr[carCount-1];
                            carCount--;
                        }
                }
            /* ******************** StringOfCars::output ********************
            Prints each Car object in the array
            If the array is empty, "NO cars" is printed instead
            */
            void output()
                {
                    if(carCount == 0)
                        {
                            cout << "NO cars";
                        }
                    else
                    {
                        for(int i = 0; i<carCount ; i++)
                        {
                            cout << endl << endl << "Car Number " << i+1 << endl<< endl;
                            ptr[i].output();
                        }
                    }
                }
    };

/* ******************** Car::operator= ********************
sets the values in the left hand object from the right hand object
*/
Car &Car::operator=(const Car & carB)
  {
  setup(carB.reportingMark, carB.carNumber, carB.kind, carB.loaded, carB.destination);

  return * this;
  }

/* ******************** operator== ********************
Car class operator functions
Takes two reference parameters
Compares the reporting mark and the car number for the two cars
*/
bool operator==(const Car &x, const Car &y)
    {
        bool status;
        if(y.reportingMark == x.reportingMark && y.carNumber == x.carNumber)
            {
                status = true;
            }
        else
            {
                status = false;
            }
        return status;
    }

void input(StringOfCars&carArray);


/* ******************** Car::setUp ********************
sets the values in the object
*/
void Car::setup(string reportingM, int carN, string k, bool l, string d)
    {
        reportingMark = reportingM;
        carNumber = carN;
        kind = k;
        loaded = l;
        destination = d;
    }

/* ******************** Car::output ********************
Prints the values in the object
*/
void Car::output()
    {
        cout << "Reporting Mark: " << reportingMark << endl;
        cout << "Car Number: " << carNumber << endl;
        cout << "Kind of Car: " << kind << endl;
        cout << "Is it loaded(True or false): " << boolalpha << loaded << endl;
        cout << "Destination: " << destination << endl;
    }
int main()
    {
        cout << "TEST 1" << endl << endl;
        Car car1("SP", 34567, "Business", true, "Salt Lake City");
        Car car2;
        car2 = car1;
        car2.output();
        cout << endl << endl << "TEST 2" << endl << endl << "STRING 1";
        StringOfCars string1;
        input(string1);
        string1.output();
        cout << endl << endl << "TEST 3" << endl << endl;
        Car car3;
        cout << "CAR 3" << endl << endl;
        string1.pop(car3);
        car3.output();
        cout << endl << "STRING 1" << endl;
        string1.output();
    }


/***************************************************
global functions
***************************************************/

/* ******************** input ********************
takes the carType, reportingMark, carNumber, kind, loaded
and destination from file
Pushes car data to String Of Cars
*/
void input(StringOfCars &carArray)
    {
        string carType;
        string reportingMark;
        int carNumber;
        string kind;
        bool loaded;
        string destination;
        ifstream inputFile;
        inputFile.open("input.txt");
        if (inputFile.fail())
            {
                cout << "ERROR: Cannot open the file. \n";
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
                if(carType == "Car")
                    {
                        Car temp(reportingMark, carNumber, kind, loaded, destination);
                        carArray.push(temp);
                    }
                else
                    {cout << "Error";}
                inputFile.clear();
                }

        inputFile.close();
    }
/*Execution Results

TEST 1

Reporting Mark: SP
Car Number: 34567
Kind of Car: Business
Is it loaded(True or false): true
Destination: Salt Lake City


TEST 2

STRING 1

Car Number 1

Reporting Mark: CN
Car Number: 819481
Kind of Car: maintenance
Is it loaded(True or false): false
Destination: NONE


Car Number 2

Reporting Mark: SLSF
Car Number: 46871
Kind of Car: business
Is it loaded(True or false): true
Destination: Memphis


Car Number 3

Reporting Mark: AOK
Car Number: 156
Kind of Car: tender
Is it loaded(True or false): true
Destination: McAlester


TEST 3

CAR 3

Reporting Mark: AOK
Car Number: 156
Kind of Car: tender
Is it loaded(True or false): true
Destination: McAlester

STRING 1


Car Number 1

Reporting Mark: CN
Car Number: 819481
Kind of Car: maintenance
Is it loaded(True or false): false
Destination: NONE


Car Number 2

Reporting Mark: SLSF
Car Number: 46871
Kind of Car: business
Is it loaded(True or false): true
Destination: Memphis
logout
Saving session...
...copying shared history...
...saving history...truncating history files...
...completed.

[Process completed]
*/

#include <iostream>
using namespace std;
#include "Catalog.h";
#include "Account.h";
#include "Schedule.h";
#include <fstream>
#include <sstream>

int main() {

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
    string path = "Andrea Sanchez.txt";

    Schedule fall17("Fall 2017", "fall2017.txt");
    cout << "~*~" << endl;
    Catalog c("catalog.txt", "prereqs.txt", "coreqs.txt");
    //initialize catalog
    //while(getline())
        //create catalog.addcourse()
    cout << "~*~" << endl;
    Account a(path);
    a.print();
    cout << "~*~" << endl;
    cout << a.completed("CMPE 102") << endl;
    cout << a.completed("CMPE 195A") << endl;
	return 0;
}

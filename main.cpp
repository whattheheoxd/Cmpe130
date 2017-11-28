#include <iostream>
using namespace std;
#include "Catalog.h";
#include "Account.h";
#include "Schedule.h";
#include "Semester.h";
#include <fstream>
#include <sstream>

int main() {
    string path = "Andrea Sanchez.txt";

    Schedule fall17("Fall 2017", "fall2017.txt");
    cout << "~*~" << endl;
    Catalog c("catalog.txt", "prereqs.txt", "coreqs.txt");
    cout << "~*~" << endl;
    Account a(path);
    a.print();
    cout << "~*~" << endl;
    cout << a.completed("CMPE 102") << endl;
    cout << a.completed("CMPE 195A") << endl;
    cout << "~*~" << endl;
    //iterate through prereqs & coreqs
    int x = c.look("CMPE 195A"); //get index value
    Requisite *pr = c.getPrereq(x); //get list of prereqs
    cout << "CMPE 195A prereqs:" << endl;

    while(pr!=NULL){ //iterate through list
        cout << pr->courseNum << endl;
        pr = pr->next;
    }

    Requisite *cr = c.getCoreq(x);
    cout << "CMPE 195A coreqs:" << endl;

    while(cr!=NULL){
        cout << cr->courseNum << endl;
        cr = cr->next;
    }
    cout << "~*~" << endl;
    Semester sem("Fall 2017");
    sem.addCourse("CMPE 102", "Assembly Language", 3, false);
    sem.addCourse("CMPE 124", "Digital Design I", 3, true);
    cout << endl;
    sem.print();
	return 0;
}

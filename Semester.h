
#ifndef SEMESTER_H_
#define SEMESTER_H_
#include <iostream>
using namespace std;
#include <vector>
#include <iomanip>
#include "Catalog.h";

class Semester {
public:
	Semester(string);
	Semester(string, int);
	~Semester();
	void addCourse(string, string, int);
	int getUnits();
	bool delCourse(string, int);
	int look(string);
	void print();
	void clearSem();
	int getSize();
	CatalogCourse* getCourse(int);
private:
	string sem;
	int units;
	int MAX_UNITS;
	vector<CatalogCourse*> courses;
};

#endif /* SEMESTER_H_ */

#ifndef CATALOG_H_
#define CATALOG_H_
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
//#include "CatalogCourse.cpp";
struct CatalogCourse {
	string courseNum;
	string course;
	int units;
	bool TE; //technical elective
};

struct Requisite{
    string courseNum;
    Requisite* next;
};

struct Reqs{
	Requisite* head;
};


//use adjacency list
class Catalog {
public:
	Catalog(string, string, string);
	Catalog(string, string, string, int);
	virtual ~Catalog();
	void create(string, string, string);
	void addCourse(string, string, int, bool);
	int look(string);
	void addPrereq(string, string);
	void addCoreq(string, string);
	int getNumCourses();
	CatalogCourse* getCourse(int);
	Requisite* getPrereq(int);
	Requisite* getCoreq(int);
private:
	int MAX_SIZE;
	int numCourses;
	CatalogCourse** courses;
	Reqs* prereqs;
	Reqs* coreqs;
};

#endif /* CATALOG_H_ */


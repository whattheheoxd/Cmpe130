#ifndef CATALOG_H_
#define CATALOG_H_
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
//#include "CatalogCourse.cpp";
struct Requisite{
    string courseNum;
    Requisite* next;
};

struct Reqs{
	Requisite* head;
};
struct CatalogCourse {
	string courseNum;
	string course;
	int priority;
	int units;
	bool TE; //technical elective
    Requisite *requi;
  	Reqs *req;
	CatalogCourse(){
        courseNum = "";
        course = "";
        units = 0;
        priority = 0;
        TE = false;
        requi = NULL;
        req = NULL;
    }
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


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
    Requisite *requi;
  	Reqs *req;
	CatalogCourse(){
        courseNum = "";
        course = "";
        units = 0;
        priority = 0;
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
	void addCourse(string, string, int);
	void addTE(string, string, int);
	int look(string);
	int lookTE(string);
	void addPrereq(string, string);
	void addCoreq(string, string);
    void addTEPrereq(string, string);
	void addTECoreq(string, string);
	int getNumCourses();
	int getNumTEs();
	CatalogCourse* getCourse(int);
	Requisite* getPrereq(int);
	Requisite* getCoreq(int);
    CatalogCourse* getTE(int);
	Requisite* getTEPrereq(int);
	Requisite* getTECoreq(int);
private:
	int MAX_SIZE;
	int numCourses;
	int numTEs;
	CatalogCourse** courses;
	CatalogCourse** TEs;
	Reqs* prereqs;
	Reqs* coreqs;
	Reqs* TEprereqs;
	Reqs* TEcoreqs;
};

#endif /* CATALOG_H_ */


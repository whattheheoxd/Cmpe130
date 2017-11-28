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
	CatalogCourse* nextpr;
	CatalogCourse* nextcr;
};

struct Reqs{
	CatalogCourse* head;
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
	CatalogCourse* getCourse(string);
	CatalogCourse* getCourse(int);
	CatalogCourse* getPrereq(string);
	CatalogCourse* getCoreq(string);
private:
	int MAX_SIZE;
	int numCourses;
	CatalogCourse** courses;
	Reqs* prereqs;
	Reqs* coreqs;
};

#endif /* CATALOG_H_ */


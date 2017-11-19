#ifndef CATALOG_H_
#define CATALOG_H_
#include <iostream>
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
	Catalog();
	Catalog(int);
	virtual ~Catalog();
	void addCourse(string, string, int, bool);
	int search(string);
	void addPrereq(string, string);
	void addCoreq(string, string);
	CatalogCourse* getCourse(string);
	CatalogCourse* getCourse(int);
private:
	int MAX_SIZE;
	int numCourses;
	CatalogCourse** courses;
	Reqs* prereqs;
	Reqs* coreqs;
};

#endif /* CATALOG_H_ */


#ifndef SEMESTER_H_
#define SEMESTER_H_
#include <iostream>
using namespace std;
#include <vector>
#include "Catalog.h";

//limit semester by unit count
class Semester {
public:
	Semester(string s){
		sem = s;
		units = 0;
		MAX_UNITS = 16;
	}

	Semester(string s, int u){
		sem = s;
		units = 0;
		MAX_UNITS = u;
	}

	~Semester();

	void addCourse(string cn, string c, int u, bool te){
		if(units+u < MAX_UNITS){
			CatalogCourse* course = new CatalogCourse;
			course->courseNum = cn;
			course->course = c;
			course->units = u;
			course->TE = te;
			course->nextpr = NULL;
			course->nextcr = NULL;
			courses.push_back(course);
			numCourses += 1;
			cout << cn << " has been added.";
		}else
			cout << "Semester full.";
	}

	int getUnits(){
		return units;
	}

	bool delCourse(string cn){
		for(int i=0; i<numCourses; i++)
			if(courses.at(i)->courseNum.compare(cn)==0){
				courses.erase(courses.begin()+i);
				return true;
			}

		return false;
	}

private:
	string sem;
	int units;
	int numCourses;
	int MAX_UNITS;
	vector<CatalogCourse*> courses;
};

#endif /* SEMESTER_H_ */

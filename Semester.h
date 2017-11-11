/*
 * Semester.h
 *
 *  Created on: Nov 2, 2017
 *      Author: Andrea
 */

#ifndef SEMESTER_H_
#define SEMESTER_H_
#include <iostream>
using namespace std;
#include "Catalog.h";

class Semester {
public:
	Semester();
	Semester(int);
	virtual ~Semester();
private:
	string sem;
	CatalogCourse** courses;
};

#endif /* SEMESTER_H_ */

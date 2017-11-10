#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H

//#include "CatalogCourse.h"
//#include "Semester.h"
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Account {
private:
	fstream acc;	//text file for schedule
	string firstName;
	string lastName;
	int studId;
	string major;
	string minor;
	//vector<CatalogCourse> completedCourses;
	//vector<CatalogCourse> incompleteCourses;
public:
	Account ();
	void setName(string firstName, string lastName);
	void setStudID(int ID);
	void setMajor(string maj);
	void setMinor(string min = NULL);
	//void addCompleteCourses(CatalogCourse obj);
	//void addIncompleteCourses(CatalogCourse obt);
	void displayStudInfo(Account obj);
};

#endif
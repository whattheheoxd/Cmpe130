#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Catalog.h"
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Account {
private:
	fstream acc;	//text file for schedule
	fstream majorFile;	//txt file for major
	fstream minorFile;	//txt file for minor
	string firstName;
	string lastName;
	int studId;
	string major;
	string minor;
	vector<CatalogCourse> completedCourses;
	vector<CatalogCourse> incompleteCourses;
public:
	Account(string firstName, string lastName, int ID, string maj, string min);
	Account(string firstName, string lastName, int ID, string maj);
	~Account();
	void setName(string firstName, string lastName);
	void setStudID(int ID);
	void setMajor(string majorName);
	void setMinor(string minorName);
	void addCompleteCourses(CatalogCourse obj);
	void addIncompleteCourses(fstream &file);
	void displayStudInfo(Account obj);
};

#endif

#include "Account.h"
//#include "Semester.h"
//#include "CatalogCourse.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

Account::Account(){
	acc.open("file.txt", std::fstream::in | std::fstream::out);
	if (acc.is_open()){
		cout << "Opening file 'file.txt'" << endl;
		//check if file template is already created
		string holder;
		getline(acc, holder);
		if (!holder.find("First Name:")) {
			acc << "First Name: \n";
			acc << "Last Name: \n";
			acc << "Student ID: \n";
			acc << "Major: \n";
			acc << "Minor: \n";
			acc << "Completed course(s): \n";
			acc << "Incomplete course(s): \n";
		}
	}
	else{
		cout << "Error opening the file\nSystem exiting..." << endl;
		exit(0);
	}
}

void Account::setName(string fName, string lName){
	firstName = fName;
	lastName = lName;

	//reset file pointer to the beginning
	acc.seekg(0, acc.beg);
	//get rid of null terminator to prevent additional \n from file
	string tmpF = fName;
	string tmpL = lName;
	tmpF.erase(tmpF.length());
	tmpL.erase(tmpL.length());
	char *buff1 = new char [tmpF.length()];
	strcpy(buff1, tmpF.c_str());
	char *buff2 = new char[tmpL.length()];
	strcpy(buff2, tmpL.c_str());
	string holder;
	getline(acc, holder);
	if (holder.find("First")) {
		//update First Name line with first name
		short pos = acc.tellp();
		acc.seekp(pos - 2);		//assumes you can go back to previous line
		acc.write(buff1, tmpF.length());
		getline(acc, holder);	//goes to next line
		//update Last Name line with last name
		pos = acc.tellp();
		acc.seekp(pos - 2);
		acc.write(buff2, tmpL.length());
	}
}

void Account::setStudID(int ID){
	studId = ID;

	//reset file pointer to the beginning
	acc.seekg(0, acc.beg);
	string holder;
	char id[9];
	memcpy(&studId, id, sizeof(int));
	getline(acc, holder);
	while (!acc.eof()) {
		if (holder.find("Student")) {
			short pos = acc.tellp();
			acc.seekp(pos - 2);
			acc.write(id, 9);
		}
		else {
			getline(acc, holder);
		}
	}
}
	
void Account::setMajor(string maj){
	major = maj;

	//reset file pointer to the beginning
	acc.seekg(0, acc.beg);
	string tmpM = maj;
	tmpM.erase(tmpM.length());
	char *buff = new char[tmpM.length()];
	strcpy(buff, tmpM.c_str());
	string holder;
	getline(acc, holder);
	while (!acc.eof()) {
		if (holder.find("Major")) {
			short pos = acc.tellp();
			acc.seekp(pos - 2);
			acc.write(buff, tmpM.length());
			break;
		}
		else {
			getline(acc, holder);
		}
	}
}
	
void Account::setMinor(string min = NULL){
	minor = min;

	//reset file pointer to the beginning
	acc.seekg(0, acc.beg);
	string tmpM = min;
	tmpM.erase(tmpM.length());
	char *buff = new char[tmpM.length()];
	strcpy(buff, tmpM.c_str());
	string holder;
	getline(acc, holder);
	while (!acc.eof()) {
		if (holder.find("Minor")) {
			short pos = acc.tellp();
			acc.seekp(pos - 2);
			acc.write(buff, tmpM.length());
			break;
		}
		else {
			getline(acc, holder);
		}
	}
}

/*
//assumes CatalogCourse title's variable is called name
void Account::addCompleteCourses(CatalogCourse obj){
	completedCourses.insert(0, obj);
	//remove from list of incomplete courses
	for (int i = 0; i < incompleteCourses.size(); i++){
		if (incompleteCourses[i] == obj){
			incompleteCourses.erase(i);
			break;
		}
	}

	//update file
	acc.seekg(0, acc.beg);
	string holder;
	char *buff = new char[obj.name.length()];
	strcpy(buff, obj.name.c_str());
	getline(acc, holder);
	while (!acc.eof()) {
		if (holder.find("Completed")) {
			short pos = acc.tellp();
			acc.seekp(pos - 2);
			acc.write(buff, obj.name.length());
			break;
		}
		else{
			getline(acc, holder);
		}
	}
}

void Account::addIncompleteCourses(CatalogCourse obj){
	incompleteCourses.push_back(obj);

	//update file
	char *buff = new char[obj.name.length()];
	strcpy(buff, obj.name.c_str());
	acc.seekg(-1, acc.end);
	acc.write(buff, obj.name.length());
}
*/

void Account::displayStudInfo(Account obj){
	cout << "Displaying student's information..." << endl;
	cout << "First Name: " << firstName << endl;
	cout << "Last Name: " << lastName << endl;
	cout << "Major: " << major << endl;
	cout << "Minor: " << minor << endl;
	cout << "Completed Course(s): " << endl;
	/*for (int i = 0; i < completedCourses.size(); i++) {
		cout << completedCourses[i] << endl;
	}
	cout << "Incomplete Course(s)" << endl;
	for (int i = 0; i < incompleteCourses.size(); i++) {
		cout << incompleteCourses[i] << endl;
	}*/
}
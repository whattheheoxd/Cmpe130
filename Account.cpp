#include "Account.h"
#include "Catalog.h"
#include <iostream>
#include <fstream>

Account::Account(string firstName, string lastName, int ID, string maj, string min) {
	setName(firstName, lastName);
	setStudID(ID);
	majorFile.open(maj, std::fstream::in);
	minorFile.open(min, std::fstream::in);
	setMajor(maj);
	setMinor(min);
	addIncompleteCourses(majorFile);
	addIncompleteCourses(minorFile);

	acc.open("file.txt", std::fstream::in | std::fstream::out);
	if (acc.is_open()) {
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
	else {
		cout << "Error opening the file\nSystem exiting..." << endl;
		exit(0);
	}
}

Account::Account(string firstName, string lastName, int ID, string maj) {
	setName(firstName, lastName);
	setStudID(ID);
	majorFile.open(maj, std::fstream::in);
	setMajor(maj);
	addIncompleteCourses(majorFile);

	acc.open("file.txt", std::fstream::in | std::fstream::out);
	if (acc.is_open()) {
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
	else {
		cout << "Error opening the file\nSystem exiting..." << endl;
		exit(0);
	}
}

Account::~Account() {
	delete this;
}

void Account::setName(string fName, string lName) {
	firstName = fName;
	lastName = lName;

	//reset file pointer to the beginning
	acc.seekg(0, acc.beg);
	//get rid of null terminator to prevent additional \n from file
	string tmpF = fName;
	string tmpL = lName;
	tmpF.erase(tmpF.length());
	tmpL.erase(tmpL.length());
	char *buff1 = new char[tmpF.length()];
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
	else {
		cout << "Unable to write first name and last name." << endl;
	}
}

void Account::setStudID(int ID) {
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
			break;
		}
		else {
			getline(acc, holder);
		}
	}
}

void Account::setMajor(string majorName) {
	major = majorName;

	//reset file pointer to the beginning
	acc.seekg(0, acc.beg);
	string tmpM = majorName;
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

void Account::setMinor(string minorName) {
	minor = minorName;

	//reset file pointer to the beginning
	acc.seekg(0, acc.beg);
	string tmpM = minorName;
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

//assumes CatalogCourse title's variable is called name
void Account::addCompleteCourses(CatalogCourse obj) {
	completedCourses.insert(completedCourses.begin(), obj);
	//remove from list of incomplete courses
	for (int i = 0; i < incompleteCourses.size(); i++) {
		if (incompleteCourses[i].course == obj.course) {
			incompleteCourses.erase(incompleteCourses.begin() + i);
			break;
		}
	}

	//update file
	acc.seekg(0, acc.beg);
	string holder;
	char *buff = new char[obj.course.length()];
	strcpy(buff, obj.course.c_str());
	getline(acc, holder);
	while (!acc.eof()) {
		if (holder.find("Completed")) {
			short pos = acc.tellp();
			acc.seekp(pos - 2);
			acc.write(buff, obj.course.length());
			break;
		}
		else {
			getline(acc, holder);
		}
	}
}

void Account::addIncompleteCourses(fstream &file) {
	string holder;
	getline(file, holder);		//skip first header line
	while (file.eof()) {
		getline(file, holder);
		CatalogCourse obj;
		char buffer[50];
		//get courseNum
		size_t tmp = holder.find(',');
		holder.copy(buffer, tmp + 1, 0);
		obj.courseNum = buffer;
		memset(buffer, '\0', 50);
		//get course
		int prevIn = tmp + 2;
		tmp = holder.find(',', tmp + 2);
		holder.copy(buffer, tmp + 1 - prevIn, prevIn);
		obj.course = buffer;
		memset(buffer, '\0', 50);
		//get units
		prevIn = tmp + 2;
		tmp = holder.find(',', tmp + 2);
		holder.copy(buffer, tmp + 1 - prevIn, prevIn);
		obj.units = stoi(buffer);
		memset(buffer, '\0', 50);
		//get technical elective or division
		prevIn = tmp + 2;
		tmp = holder.find(',', tmp + 2);
		if (tmp != std::string::npos) {		//check if neither TE or Division
			holder.copy(buffer, tmp + 1 - prevIn, prevIn);
			if (buffer == "TE") {
				obj.TE = true;
			}
			else if (buffer == "UD" || buffer == "LD") {
				if (buffer == "UD")
					obj.Division = true;
				else
					obj.Division = false;
			}
		}
		incompleteCourses.push_back(obj);
	}
}

void Account::displayStudInfo(Account obj) {
	cout << "Displaying student's information..." << endl;
	cout << "First Name: " << firstName << endl;
	cout << "Last Name: " << lastName << endl;
	cout << "Major: " << major << endl;
	cout << "Minor: " << minor << endl;
	cout << "Completed Course(s): " << endl;
	for (int i = 0; i < completedCourses.size(); i++) 
		cout << completedCourses[i].courseNum << " " << completedCourses[i].course << endl;
	cout << "Incomplete Course(s)" << endl;
	for (int i = 0; i < incompleteCourses.size(); i++)
		cout << incompleteCourses[i].courseNum << " " << incompleteCourses[i].course << endl;
}

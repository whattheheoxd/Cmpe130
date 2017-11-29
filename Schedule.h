
#ifndef SCHEDULE_H_
#define SCHEDULE_H_
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

struct ScheduleCourse{
	string courseNum;
	string course;
	int units;
	int courseID;
	int section;
	//data struture to hold days & times?
	//string days[]
	//int times[]
	//adjacency matrix of times?
	//Mon-Fri columns, rows = times?

};

class Schedule {
public:
	Schedule(string, string);
	Schedule(string, string, int);
	~Schedule();
	void create(string); //get txt file
	void addCourse(string, string, int, int, int);
	bool available(string); //for determining if the course is available when adding to the Semester
	//getCourses uses binary search to return a vector of ScheduleCourses
	//this fn is used for AFTER the Semester obj has been created
	//we will NOT consider schedule conflicts when creating the semester
	vector<ScheduleCourse*> getCourses(string);
	int getLeft(int, int, string);
	int getRight(int, int, string);

private:
	string semester;
	ScheduleCourse** courses;
	int MAX_SIZE;
	int numCourses;
};

#endif /* SCHEDULE_H_ */

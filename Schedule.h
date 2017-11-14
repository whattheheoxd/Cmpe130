/*
 * Schedule.h
 *
 *  Created on: Nov 2, 2017
 *      Author: Andrea
 */

#ifndef SCHEDULE_H_
#define SCHEDULE_H_
#include <iostream>
#include <vector>
using namespace std;

struct ScheduleCourse{
	string courseNum;
	string course;
	int units;
	int courseID;
	//data struture to hold days & times?
	//string days[]
	//int times[]
	//adjacency matrix of times?
	//Mon-Fri columns, rows = times?

};

class Schedule {
public:
	Schedule(string);
	Schedule(string, int);
	virtual ~Schedule();
	void addCourse(string, string, int, int);
	ScheduleCourse* getCourse(int);
	vector<ScheduleCourse*> getCourses(string);
	vector<int> search(string); //return array of course ids
private:
	string semester;
	ScheduleCourse** courses;
	int MAX_SIZE;
	int numCourses;
};

#endif /* SCHEDULE_H_ */


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
	ScheduleCourse* getCourse(int);
	vector<ScheduleCourse*> getCourses(string);
	vector<int> look(string); //return array of course ids
private:
	string semester;
	ScheduleCourse** courses;
	int MAX_SIZE;
	int numCourses;
};

#endif /* SCHEDULE_H_ */

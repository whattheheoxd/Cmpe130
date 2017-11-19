
#include "Schedule.h"

Schedule::Schedule(string s) {
	// TODO Auto-generated constructor stub
	MAX_SIZE = 250;
	numCourses = 0;
	semester = s;
	courses = new ScheduleCourse*[MAX_SIZE];
}

Schedule::Schedule(string s, int n) {
	// TODO Auto-generated constructor stub
	MAX_SIZE = n;
	numCourses = 0;
	semester = s;
	courses = new ScheduleCourse*[MAX_SIZE];
}

Schedule::~Schedule() {
	// TODO Auto-generated destructor stub
}

//insertion sort
void Schedule::addCourse(string cn, string c, int u, int id){
	if(numCourses < MAX_SIZE){
		ScheduleCourse* course = new ScheduleCourse;
		course->courseNum = cn;
		course->course = c;
		course->units = u;
		course->courseID = id;
		courses[numCourses] = course;
		numCourses += 1;

		bool done = false;
		int i = numCourses-1;
		while(i>0 && !done){
			if(courses[i]->courseID < courses[i-1]->courseID){
				ScheduleCourse* temp = courses[i];
				courses[i] = courses[i-1];
				courses[i-1] = courses[i];
			}else
				done = true;
			i--;
		}

		cout << id << " " << cn << " has been added.";
	}else
		cout << "Catalog full.";
}

//binary search
ScheduleCourse* Schedule::getCourse(int id){
	int i = 0, lo = 0, hi = numCourses-1, m;

	while(lo <= hi){
		m = (lo+hi)/2;
		if(courses[m]->courseID < id)
			hi = m - 1;
		else if(courses[m]->courseID > id)
			lo = m + 1;
		else return courses[m];
	}
	return NULL;
}

//linear search - unsorted by courseNum
vector<ScheduleCourse*> Schedule::getCourses(string cn){
	vector<ScheduleCourse*> c;
	for(int i=0; i < numCourses; i++)
		if(courses[i]->courseNum.compare(cn)==0)
			c.push_back(courses[i]);

	return c;
}

//linear search
vector<int> Schedule::search(string cn){
	vector<int> c;
	for(int i=0; i < numCourses; i++)
		if(courses[i]->courseNum.compare(cn)==0)
			c.push_back(courses[i]->courseID);
	return c;
}


#include "Schedule.h"

Schedule::Schedule(string s, string path) {
	// TODO Auto-generated constructor stub
	MAX_SIZE = 250;
	numCourses = 0;
	semester = s;
	courses = new ScheduleCourse*[MAX_SIZE];
	create(path);
}

Schedule::Schedule(string s, string path, int n) {
	// TODO Auto-generated constructor stub
	MAX_SIZE = n;
	numCourses = 0;
	semester = s;
	courses = new ScheduleCourse*[MAX_SIZE];
	create(path);
}

Schedule::~Schedule() {
	// TODO Auto-generated destructor stub
}

void Schedule::create(string path){
    ifstream file;
    file.open(path.c_str());
    string s, t, courseNum, course, x, y, z;
    int section, courseID, units;
    bool te;
    if(file.is_open()){
        //begin ScheduleCourse obj initialization
        while(getline(file, s)){
            //courseNum, course, section, courseID, units
            stringstream stream(s);
            getline(stream, courseNum, ',');
            getline(stream, course, ',');
            getline(stream, x, ',');
            stringstream sc(x);
            sc >> section;
            getline(stream, y, ',');
            stringstream id(y);
            id >> courseID;
            getline(stream, z, ',');
            stringstream u(z);
            u >> units;
            addCourse(courseNum, course, section, courseID, units);
            cout << endl;
        }
    }
}

//insertion sort
void Schedule::addCourse(string cn, string c, int s, int id, int u){
	if(numCourses < MAX_SIZE){
		ScheduleCourse* course = new ScheduleCourse;
		course->courseNum = cn;
		course->course = c;
		course->section = s;
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
				courses[i-1] = temp;
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
vector<int> Schedule::look(string cn){
	vector<int> c;
	for(int i=0; i < numCourses; i++)
		if(courses[i]->courseNum.compare(cn)==0)
			c.push_back(courses[i]->courseID);
	return c;
}

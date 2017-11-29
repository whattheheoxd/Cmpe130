
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
			if(courses[i]->courseNum.compare(courses[i-1]->courseNum) < 0 ){
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

//binary search - check if course cn is in the schedule
bool Schedule::available(string cn){
	int i = 0, lo = 0, hi = numCourses-1, m;

while(lo <= hi){
		m = (lo+hi)/2;
		if(courses[m]->courseNum.compare(cn) > 0)
			hi = m - 1;
		else if(courses[m]->courseNum.compare(cn) < 0)
			lo = m + 1;
		else return true;
	}
	//if(lo > hi)
        return false;
}

int Schedule::getRight(int l, int r, string cn){
    int m;

    while(r-l>1){
        m=l+(r-l)/2;
        if(courses[m]->courseNum.compare(cn) > 0)
            r = m;
        else
            l = m;
    }

    return l;
}

int Schedule::getLeft(int l, int r, string cn){
    int m;

    while(r-l>1){
        m =l+(r-l)/2;
        if(courses[m]->courseNum.compare(cn) < 0)
            l = m;
        else
            r = m;
    }

    return r;
}

vector<ScheduleCourse*> Schedule::getCourses(string cn){
	vector<ScheduleCourse*> c;

    int l = getLeft(-1, numCourses-1, cn);
    int r = getRight(0, numCourses, cn);

    // What if the element doesn't exists in the array?
    // The checks helps to trace that element exists

    for(int i=l; i <= r; i++) //right - left + 1
		//if(courses[i]->courseNum.compare(cn)==0)
			c.push_back(courses[i]);
    return c;
}

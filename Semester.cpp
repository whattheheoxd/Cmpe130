
#include "Semester.h";

Semester::Semester(string s){
	sem = s;
	units = 0;
	MAX_UNITS = 16;
}

Semester::Semester(string s, int u){
	sem = s;
	units = 0;
	MAX_UNITS = u;
}

Semester::~Semester();

void Semester::addCourse(string cn, string c, int u, bool te){
	if(units+u < MAX_UNITS){
		CatalogCourse* course = new CatalogCourse;
		course->courseNum = cn;
		course->course = c;
		course->units = u;
		course->TE = te;
		course->nextpr = NULL;
		course->nextcr = NULL;
		courses.push_back(course);
		numCourses += 1;
		cout << cn << " has been added.";
	}else
		cout << "Semester full.";
}

int Semester::getUnits(){
	return units;
}

bool Semester::delCourse(string cn){
	int i = search(cn);
	if(i!=-1){
		courses.erase(courses.begin()+i);
		return true;
	}else
		return false;
}

int Semester::search(string cn){
	for(int i=0; i<numCourses; i++)
		if(courses.at(i)->courseNum.compare(cn)==0)
			return i;

	return -1;
}

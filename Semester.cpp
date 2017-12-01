
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

Semester::~Semester(){
}

void Semester::addCourse(string cn, string c, int u){
	if(units+u < MAX_UNITS){
		CatalogCourse* course = new CatalogCourse;
		course->courseNum = cn;
		course->course = c;
		course->units = u;
		courses.push_back(course);
		units+=u;
		//cout << cn << " has been added.";
	}else
		cout << "Semester full." << endl;
}

int Semester::getUnits(){
	return units;
}

bool Semester::delCourse(string cn, int u){
	int i = look(cn);
	if(i!=-1){
		courses.erase(courses.begin()+i);
		units -=u;
		return true;
	}else
		return false;
}

int Semester::look(string cn){
	for(int i=0; i<courses.size(); i++)
		if(courses.at(i)->courseNum.compare(cn)==0)
			return i;

	return -1;
}

void Semester::print(){
    cout << "Course\t\tCourse Name\t\tUnits" << endl;
    for(int i=0; i<courses.size(); i++){
        cout << setw(12) << left << courses[i]->courseNum << setw(40) << left << courses[i]->course << setw(2) << courses[i]->units;
        cout << endl;
    }
}

void Semester::clearSem(){
    courses.clear();
    units = 0;
}

int Semester::getSize(){
    return courses.size();
}

CatalogCourse* Semester::getCourse(int i){
    return courses[i];
}


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

void Semester::addCourse(string cn, string c, int u, bool te){
	if(units+u < MAX_UNITS){
		CatalogCourse* course = new CatalogCourse;
		course->courseNum = cn;
		course->course = c;
		course->units = u;
		course->TE = te;
		courses.push_back(course);
		cout << cn << " has been added.";
	}else
		cout << "Semester full.";
}

int Semester::getUnits(){
	return units;
}

bool Semester::delCourse(string cn){
	int i = look(cn);
	if(i!=-1){
		courses.erase(courses.begin()+i);
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
        cout << courses[i]->courseNum << "\t" << courses[i]->course << "\t" << courses[i]->units;
        if(courses[i]->TE) cout << "\tTE";
        cout << endl;
    }
}

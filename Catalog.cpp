#include "Catalog.h"
//use adjacency list

Catalog::Catalog() {
	// TODO Auto-generated constructor stub
	MAX_SIZE = 100;
	numCourses = 0;
	courses = new CatalogCourse*[MAX_SIZE];
	prereqs = new Reqs[MAX_SIZE];
	coreqs = new Reqs[MAX_SIZE];
	for(int i=0; i<MAX_SIZE; i++){
		prereqs[i].head = NULL;
		coreqs[i].head = NULL;
	}

}

Catalog::Catalog(int size) {
	// TODO Auto-generated constructor stub
	MAX_SIZE = size;
	numCourses = 0;
	courses = new CatalogCourse*[MAX_SIZE];
	prereqs = new Reqs[MAX_SIZE];
	coreqs = new Reqs[MAX_SIZE];
	for(int i=0; i<MAX_SIZE; i++){
		prereqs[i].head = NULL;
		coreqs[i].head = NULL;
	}
}

Catalog::~Catalog() {
	// TODO Auto-generated destructor stub

}

//sort by courseNum
//ex. c.addCourse("MATH 30", "Calculus I", 3, false);
void Catalog::addCourse(string cn, string c, int u, bool te){
	if(numCourses < MAX_SIZE){
		CatalogCourse* course = new CatalogCourse;
		course->courseNum = cn;
		course->course = c;
		course->units = u;
		course->TE = te;
		course->nextpr = NULL;
		course->nextcr = NULL;
		courses[numCourses] = course;
		numCourses += 1;

		bool done = false;
		int i = numCourses-1;
		while(i>0 && !done){
			if(courses[i]->courseNum.compare(courses[i-1]->courseNum) > 0){
				CatalogCourse* temp = courses[i];
				courses[i] = courses[i-1];
				courses[i-1] = courses[i];
			}else
				done = true;
			i--;
		}

		cout << cn << " has been added.";
	}else
		cout << "Catalog full.";
}

//catalog sorted by courseNum - binary search
int Catalog::search(string cn){
    /*
    for(int i = 0; i < numCourses; i++){
        if(courses[i]->courseNum.compare(cn) == 0)
            return i;
    }
    return -1;
    */
	int i = 0, lo = 0, hi = numCourses-1, m;

	while(lo <= hi){
		m = (lo+hi)/2;
		if(courses[m]->courseNum.compare(cn) > 0)
			hi = m - 1;
		else if(courses[m]->courseNum.compare(cn) < 0)
			lo = m + 1;
		else return m;
	}
	//if(lo > hi)
        return -1;

}

void Catalog::addPrereq(string c, string pr){ //adding edge
	int ci = search(c); //find indicated courses
	int pri = search(pr);

	if(ci==-1 || pri==-1){
		cout << "Prerequisite relation cannot be added: ";
		if(ci==-1) cout << c << " is not in the catalog.";
		if(pri==-1) cout << pr << " is not in the catalog.";
	}else{ //both courses in the catalog, add prereq relation (edge)
		courses[pri]->nextpr = prereqs[ci].head;
		prereqs[ci].head = courses[pri];
		cout << c << "'s prerequisite " << pr << " has been added.";
	}
}

void Catalog::addCoreq(string c, string cr){ //adding edge
	int ci = search(c); //find indicated courses
	int cri = search(cr);

	if(ci==-1 || cri==-1){
		cout << "Corequisite relation cannot be added: ";
		if(ci==-1) cout << c << " is not in the catalog.";
		if(cri==-1) cout << cr << " is not in the catalog.";
	}else{ //both courses in the catalog, add prereq relation (edge)
		courses[cri]->nextcr = prereqs[ci].head;
		prereqs[ci].head = courses[cri];
		cout << c << "'s corequisite " << cr << " has been added.";
	}
}

//binary search
CatalogCourse* Catalog::getCourse(string cn){
	int m = search(cn);
	return (m!=-1) ? courses[m] : NULL;
}

CatalogCourse* Catalog::getCourse(int cn){
	return courses[cn];
}

#include "Catalog.h"
//use adjacency list

Catalog::Catalog(string c, string pr, string cr) {
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
    create(c, pr, cr);
}

Catalog::Catalog(string c, string pr, string cr, int size) {
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
	create(c, pr, cr);
}

Catalog::~Catalog() {
	// TODO Auto-generated destructor stub

}

void Catalog::create(string c, string pr, string cr){
    ifstream file;
    file.open(c.c_str());
    string s, t, courseNum, course, x;
    int section, courseID, units;
    bool te;
    if(file.is_open()){
        //begin CatalogCourse obj initialization
        //CourseNum, course, units, TE
        while(getline(file, s)){
            stringstream stream(s);
            getline(stream, courseNum, ',');
            getline(stream, course, ',');
            getline(stream, x, ',');
            stringstream u(x);
            u >> units;
            te = getline(stream, t, ',');

            addCourse(courseNum, course, units, te);
            cout << endl;
        }
        file.close();
    }

    file.open(pr.c_str());
    if(file.is_open()){
        while(getline(file, s)){
            stringstream stream(s);
            getline(stream, courseNum, ',');
            getline(stream, course, ',');
            addPrereq(courseNum, course);
            cout << endl;
        }
        file.close();
    }

    file.open(cr.c_str());
    if(file.is_open()){
        while(getline(file, s)){
            stringstream stream(s);
            getline(stream, courseNum, ',');
            getline(stream, course, ',');
            addCoreq(courseNum, course);
            cout << endl;
        }
        file.close();
    }
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
		courses[numCourses] = course;
		numCourses += 1;

		bool done = false;
		int i = numCourses-1;
		while(i>0 && !done){
			if(courses[i]->courseNum.compare(courses[i-1]->courseNum) < 0){
				CatalogCourse* temp = courses[i];
				courses[i] = courses[i-1];
				courses[i-1] = temp;
			}else
				done = true;
			i--;
		}

		cout << cn << " has been added.";
	}else
		cout << "Catalog full.";
}

//catalog sorted by courseNum - binary search
int Catalog::look(string cn){
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
	int ci = look(c); //find indicated courses
	int pri = look(pr);

	if(ci==-1 || pri==-1){
		cout << "Prerequisite relation cannot be added: ";
		if(ci==-1) cout << c << " is not in the catalog.";
		if(pri==-1) cout << pr << " is not in the catalog.";
	}else{ //both courses in the catalog, add prereq relation (edge)
	    Requisite *pre = new Requisite();
	    pre->courseNum = pr;
	    pre->next = prereqs[ci].head;
	    prereqs[ci].head = pre;
		cout << c << "'s prerequisite " << pr << " has been added.";
	}
}

void Catalog::addCoreq(string c, string cr){ //adding edge
	int ci = look(c); //find indicated courses
	int cri = look(cr);

	if(ci==-1 || cri==-1){
		cout << "Corequisite relation cannot be added: ";
		if(ci==-1) cout << c << " is not in the catalog.";
		if(cri==-1) cout << cr << " is not in the catalog.";
	}else{ //both courses in the catalog, add coreq relation (edge)
        Requisite *co = new Requisite();
	    co->courseNum = cr;
	    co->next = coreqs[ci].head;
	    coreqs[ci].head = co;
		cout << c << "'s corequisite " << cr << " has been added.";
	}
}

CatalogCourse* Catalog::getCourse(int cn){
	return (cn>=0 && cn<numCourses) ? courses[cn] : NULL;
}

Requisite* Catalog::getPrereq(int cn){
    return (cn>=0 && cn<numCourses) ? prereqs[cn].head : NULL;
}

Requisite* Catalog::getCoreq(int cn){
    return (cn>=0 && cn<numCourses) ? coreqs[cn].head : NULL;
}

int Catalog::getNumCourses(){
    return numCourses;
}

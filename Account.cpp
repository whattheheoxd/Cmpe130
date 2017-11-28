#include "Account.h"

Account::Account(string path){
    ifstream file;
    file.open(path.c_str());
    string s, t, courseNum, course, units, p;
    int x;
    bool te;
    if(file.is_open()){
        //account file required that name, id, & major be there. minor optional
        getline(file, name);

        getline(file, s); //id
        stringstream id(s);
        id >> studId;

        getline(file, major);

        p = ""; //minor
        getline(file, p); //could be "." or minor
        if(p.compare(".")!=0){ //minor exists
            minor = p;
            getline(file, p);
        }else{
            minor = "no minor";
        }

        //begin CatalogCourse obj initialization
        while(getline(file, s)){
            stringstream stream(s);
            getline(stream, courseNum, ',');
            getline(stream, course, ',');
            getline(stream, units, ',');
            stringstream u(units);
            u >> x;
            te = getline(stream, t, ',');

            addCourse(courseNum, course, x, te);
        }
    }
}

Account::~Account()
{
    //dtor
}

void Account::print()
{
    CatalogCourse *cc = NULL;
    cout << name << endl;
    cout << studId << endl;
    cout << major << endl;
    cout << minor << endl;
    for(int i=0; i<completedCourses.size(); i++){
        cc = completedCourses[i];
        cout << cc->courseNum << " " << cc->course << " " << cc->units;
        if(cc->TE) cout << " TE";
        cout << endl;
    }
}

void Account::addCourse(string cn, string c, int u, bool te){
    CatalogCourse *cc = new CatalogCourse();
    cc->courseNum = cn;
    cc->course = c;
    cc->units = u;
    cc->TE = te;
    cc->nextcr = NULL;
    cc->nextpr = NULL;
    completedCourses.push_back(cc);

    bool done = false;
    int i = completedCourses.size()-1;
    while(i>0 && !done){ //insertion sort
        if(completedCourses[i]->courseNum.compare(completedCourses[i-1]->courseNum) < 0){
            CatalogCourse* temp = completedCourses[i];
            completedCourses[i] = completedCourses[i-1];
            completedCourses[i-1] = temp;
        }else
            done = true;
        i--;
    }
}
//binary search
bool Account::completed(string s){ //returns true if course is completed
    int lo = 0, hi = completedCourses.size()-1, m;
    while(lo <= hi){
		m = (lo+hi)/2;
		if(completedCourses[m]->courseNum.compare(s) > 0)
			hi = m - 1;
		else if(completedCourses[m]->courseNum.compare(s) < 0)
			lo = m + 1;
		else return true;
	}
	return false;
}

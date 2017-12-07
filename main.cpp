#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <ctime>
#include "Catalog.h";
#include "Account.h";
#include "Semester.h";
using namespace std;
const int unitsCap = 16;

bool checkPre(string course, Catalog &catalog, Account &account)
{
    int x = catalog.look(course);
    Requisite *pr = catalog.getPrereq(x);

    if(pr==NULL) return true; //no prereqs, check is true
    else{
        while(pr!=NULL)
        {
            if(account.completed(pr->courseNum))
                pr = pr->next;
            else //prereq not met
                return false;
        }
        return true;
    }
}

bool checkCo(string course, Catalog &catalog, Account &account)
{
    int x = catalog.look(course);
    Requisite *cr = catalog.getCoreq(x);

    if(cr==NULL) return true; //no prereqs, check is true
    else{
        while(cr!=NULL)
        {
            if(account.completed(cr->courseNum))
                 cr = cr->next;
            else
                return false;
        }
        return true;
    }
}


void getStartingPts(Account &acc, Catalog &cat, int unitsCap, vector<CatalogCourse *> &startPtrs) 					//DONE
{
    CatalogCourse *obj;
	for (int i = 0; i < cat.getNumCourses(); i++)
	{
	    obj = cat.getCourse(i);
		if (cat.getPrereq(i) == NULL)
			startPtrs.push_back(obj);
		else
        {
            Requisite *pr = cat.getPrereq(i);
            while(pr!=NULL)
            {
                if(acc.completed(pr->courseNum))
                    pr = pr->next;
                else
                    break;
            }
			startPtrs.push_back(obj);
        }
	}
	return;
}

void modFWAlgo(Account &acc, Catalog &cat, int unitsCap, vector<CatalogCourse *> &startPtrs, Semester &sem){
    int hold = unitsCap;
    int remover;
    int it = 0;

    for(int i = 0; i < startPtrs.size(); i++){
        string stpt = startPtrs[i]->courseNum;
        int ci = cat.look(stpt);

        if(hold>=0){
            if(acc.completed(stpt))
                continue;
            else{
                bool prereq, coreq;
                Requisite *pr, *cr;
                pr = cat.getPrereq(ci);
                cr = cat.getCoreq(ci);

                if(pr==NULL && cr==NULL)
                     sem.addCourse(stpt, startPtrs[i]->course, startPtrs[i]->units);
                else if(pr!=NULL && cr==NULL){
                    //check prereqs
                    prereq = checkPre(stpt, cat, acc);
                    if(prereq){
                         sem.addCourse(stpt, startPtrs[i]->course, startPtrs[i]->units);
                         hold = hold - startPtrs[i]->units;
                    }
                }
                else if(pr==NULL && cr!=NULL){
                    //only check coreqs
                    coreq = checkCo(stpt, cat, acc);
                    int idk = cat.look(cr->courseNum);
                    CatalogCourse *cc = cat.getCourse(idk);
                    bool preofCo = checkPre(cr->courseNum,cat,acc);

                    if(preofCo && sem.look(cr->courseNum)==-1)
                    {
                        if(hold >= cc->units + startPtrs[i]->units){
                            sem.addCourse(stpt, startPtrs[i]->course, startPtrs[i]->units);
                            sem.addCourse(cc->courseNum, cc->course, cc->units);
                            hold = hold - cc->units - startPtrs[i]->units;
                        }
                        else if(hold <= cc->units + startPtrs[i]->units && hold >= cc->units){
                            sem.addCourse(cc->courseNum, cc->course, cc->units);
                            hold = hold - cc->units;
                        }
                    }
                    else if(preofCo && sem.look(cr->courseNum)!=-1){
                        sem.addCourse(stpt, startPtrs[i]->course, startPtrs[i]->units);
                        hold = hold - startPtrs[i]->units;
                    }
                }
                else{
                    prereq = checkPre(stpt, cat, acc);
                    coreq  = checkCo(stpt, cat, acc);

                    if(prereq && coreq ){
                        sem.addCourse(stpt, startPtrs[i]->course, startPtrs[i]->units);
                        hold = hold - startPtrs[i]->units;
                    }else if(!prereq && coreq)
                        continue;
                    else if(prereq && !coreq){
                        int idk = cat.look(cr->courseNum);
                        CatalogCourse *cc = cat.getCourse(idk);
                        bool preofCo = checkPre(cr->courseNum,cat,acc);

                        if(preofCo && sem.look(cr->courseNum)==-1)
                        {
                            if(hold >= cc->units + startPtrs[i]->units){
                                sem.addCourse(stpt, startPtrs[i]->course, startPtrs[i]->units);
                                sem.addCourse(cc->courseNum, cc->course, cc->units);
                                hold = hold - cc->units - startPtrs[i]->units;
                            }
                            else if(hold <= cc->units + startPtrs[i]->units && hold >= cc->units){
                                sem.addCourse(cc->courseNum, cc->course, cc->units);
                                hold = hold - cc->units;
                            }
                        }
                        else if(preofCo && sem.look(cr->courseNum)!=-1){
                            sem.addCourse(stpt, startPtrs[i]->course, startPtrs[i]->units);
                            hold = hold - startPtrs[i]->units;
                        }
                    }
                }
            }
        }
    }

    if(sem.getUnits() == 0)
        return;
    else{
        cout << "------------\n";
        sem.print();
        for(int k = 0; k < sem.getSize(); k++)
        acc.addCourse(sem.getCourse(k)->courseNum,sem.getCourse(k)->course,sem.getCourse(k)->units);

        sem.clearSem();
        startPtrs.clear();

        getStartingPts(acc, cat, unitsCap, startPtrs);
        modFWAlgo(acc, cat, unitsCap, startPtrs, sem);
    }
}

int main()
{
    //create static catalogs
    Catalog cmpe_cat("catalog_cmpe.txt", "prereqs_cmpe.txt", "coreqs_cmpe.txt", "CMPE");
    Catalog se_cat("catalog_se.txt", "prereqs_se.txt", "coreqs_se.txt", "SE");

    //create accounts
    Account accEmpCMPE("empty_cmpe.txt");
    Account accFrsCMPE("freshman_cmpe.txt");
    Account accJunCMPE("junior_cmpe.txt");
    Account accSenCMPE("senior_cmpe.txt");
    Account accEmpSE("empty_se.txt");
    Account accFrsSE("freshman_se.txt");
    Account accJunSE("junior_se.txt");
    Account accSenSE("senior_se.txt");

    //create dynamic objects
    vector<CatalogCourse *> startPtrsCMPE;
    vector<CatalogCourse *> startPtrsSE;
    Semester sem("Schedule");

    ////////////////////////////CMPE Test Accounts//////////////////////////

    cout << "------------------------------------------------------------\n";
    cout << "CMPE Empty Account Completed Courses\n";
    cout << "------------\n";
    for(int i=0; i<accEmpCMPE.getNumCourses();i++)
        cout << accEmpCMPE.getCourse(i)->courseNum << endl;

    cout << "------------------------------------------------------------\n";
    cout << "Begin Shortest Path to Graduation Schedule for CMPE Empty\n";
    getStartingPts(accEmpCMPE, cmpe_cat, unitsCap, startPtrsCMPE);
    modFWAlgo(accEmpCMPE, cmpe_cat, unitsCap, startPtrsCMPE, sem);

    startPtrsCMPE.clear();

    cout << "------------------------------------------------------------\n";
    cout << "CMPE Freshman Account Completed Courses\n";
    cout << "------------\n";
    for(int i=0; i<accFrsCMPE.getNumCourses();i++)
    cout << accFrsCMPE.getCourse(i)->courseNum << endl;

    cout << "------------------------------------------------------------\n";
    cout << "Begin Shortest Path to Graduation Schedule for CMPE Freshman\n";
    getStartingPts(accFrsCMPE, cmpe_cat, unitsCap, startPtrsCMPE);
    modFWAlgo(accFrsCMPE, cmpe_cat, unitsCap, startPtrsCMPE, sem);

    startPtrsCMPE.clear();

    cout << "------------------------------------------------------------\n";
    cout << "CMPE Junior Account Completed Courses\n";
    cout << "------------\n";
    for(int i=0; i<accJunCMPE.getNumCourses();i++)
        cout << accJunCMPE.getCourse(i)->courseNum << endl;

    cout << "------------------------------------------------------------\n";
    cout << "Begin Shortest Path to Graduation Schedule for CMPE Junior\n";
    getStartingPts(accJunCMPE, cmpe_cat, unitsCap, startPtrsCMPE);
    modFWAlgo(accJunCMPE, cmpe_cat, unitsCap, startPtrsCMPE, sem);

    startPtrsCMPE.clear();

    cout << "------------------------------------------------------------\n";
    cout << "CMPE Senior Account Completed Courses\n";
    cout << "------------\n";
    for(int i=0; i<accSenCMPE.getNumCourses();i++)
        cout << accSenCMPE.getCourse(i)->courseNum << endl;

    cout << "------------------------------------------------------------\n";
    cout << "Begin Shortest Path to Graduation Schedule for CMPE Senior\n";
    getStartingPts(accSenCMPE, cmpe_cat, unitsCap, startPtrsCMPE);
    modFWAlgo(accSenCMPE, cmpe_cat, unitsCap, startPtrsCMPE, sem);

    startPtrsCMPE.clear();

    ////////////////////////////SE Test Accounts////////////////////////////

    cout << "------------------------------------------------------------\n";
    cout << "SE Empty Account Completed Courses\n";
    cout << "------------\n";
    for(int i=0; i<accEmpSE.getNumCourses();i++)
        cout << accEmpSE.getCourse(i)->courseNum << endl;

    cout << "------------------------------------------------------------\n";
    cout << "Begin Shortest Path to Graduation Schedule for SE Empty\n";
    getStartingPts(accEmpSE, se_cat, unitsCap, startPtrsSE);
    modFWAlgo(accEmpSE, se_cat, unitsCap, startPtrsSE, sem);

    startPtrsSE.clear();

    cout << "------------------------------------------------------------\n";
    cout << "SE Freshman Account Completed Courses\n";
    cout << "------------\n";
    for(int i=0; i<accFrsSE.getNumCourses();i++)
        cout << accFrsSE.getCourse(i)->courseNum << endl;

    cout << "------------------------------------------------------------\n";
    cout << "Begin Shortest Path to Graduation Schedule for SE Freshman\n";
    getStartingPts(accFrsSE, se_cat, unitsCap, startPtrsSE);
    modFWAlgo(accFrsSE, se_cat, unitsCap, startPtrsSE, sem);

    startPtrsSE.clear();

    cout << "------------------------------------------------------------\n";
    cout << "SE Junior Account Completed Courses\n";
    cout << "------------\n";
    for(int i=0; i<accJunSE.getNumCourses();i++)
        cout << accJunSE.getCourse(i)->courseNum << endl;

    cout << "------------------------------------------------------------\n";
    cout << "Begin Shortest Path to Graduation Schedule for SE Junior\n";
    getStartingPts(accJunSE, se_cat, unitsCap, startPtrsSE);
    modFWAlgo(accJunSE, se_cat, unitsCap, startPtrsSE, sem);

    startPtrsSE.clear();

    cout << "------------------------------------------------------------\n";
    cout << "SE Senior Account Completed Courses\n";
    cout << "------------\n";
    for(int i=0; i<accSenSE.getNumCourses();i++)
        cout << accSenSE.getCourse(i)->courseNum << endl;

    cout << "------------------------------------------------------------\n";
    cout << "Begin Shortest Path to Graduation Schedule for SE Senior\n";
    getStartingPts(accSenSE, se_cat, unitsCap, startPtrsSE);
    modFWAlgo(accSenSE, se_cat, unitsCap, startPtrsSE, sem);

    startPtrsSE.clear();

	return 0;
}

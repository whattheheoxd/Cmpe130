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
																																																						//Close FW algo
//checkPre("MATH 031", &cmpe, &a)
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
            {
                return false;
            }
        }
        return true;
    }
    //iterating through 1B
}//1A not completed - yet found in current
//

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
            {
                return false;
            }
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
		if (cat.getPrereq(i) == NULL) 																																									//set starting points
		{
		    //cout << "Starting point: " << obj->courseNum << endl;
			startPtrs.push_back(obj);
		}
		else
        {
            Requisite *pr = cat.getPrereq(i);
            while(pr!=NULL)
            {
                if(acc.completed(pr->courseNum))
                    pr = pr->next;
                else
                {
                    break;
                }
            }
            //cout << "Starting point : " << obj->courseNum << endl;
			startPtrs.push_back(obj);
        }
	}
	return;
}

void modFWAlgo(Account &acc, Catalog &cat, int unitsCap, vector<CatalogCourse *> &startPtrs, Semester &sem)
{
  int hold = unitsCap;
  int remover;
  int it = 0;

    for(int i = 0; i < startPtrs.size(); i++)
    {
        string stpt = startPtrs[i]->courseNum;
        int ci = cat.look(stpt);
        if(hold>=0){
            if(acc.completed(stpt)) continue;
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
                    if(prereq)
                         sem.addCourse(stpt, startPtrs[i]->course, startPtrs[i]->units);
                }
                else if(pr==NULL && cr!=NULL){
                    //only check coreqs
                    coreq = checkCo(stpt, cat, acc);
                    if(coreq)
                         sem.addCourse(stpt, startPtrs[i]->course, startPtrs[i]->units);
                }
                else{
                    prereq = checkPre(stpt, cat, acc);
                    coreq  = checkCo(stpt, cat, acc);
                    if(prereq && coreq)
                    {
                        sem.addCourse(stpt, startPtrs[i]->course, startPtrs[i]->units);
                    }
                    else if(!prereq && coreq)
                    {
                        continue;
                    }
                    else if(prereq && !coreq)
                    {
                        int idk = cat.look(cr->courseNum);
                        CatalogCourse *cc = cat.getCourse(idk);
                        bool preofCo = checkPre(cr->courseNum,cat,acc);
                        if(preofCo && !sem.look(cr->courseNum))
                        {
                            if(hold >= cc->units + startPtrs[i]->units)
                            {
                                sem.addCourse(stpt, startPtrs[i]->course, startPtrs[i]->units);
                                sem.addCourse(cc->courseNum, cc->course, cc->units);
                                hold = hold - cc->units - startPtrs[i]->units;
                            }
                            if(hold <= cc->units + startPtrs[i]->units && hold >= cc->units)
                            {
                                sem.addCourse(cc->courseNum, cc->course, cc->units);
                                hold = hold - cc->units;
                            }
                        }
                        else if(preofCo && sem.look(cr->courseNum))
                        {
                            sem.addCourse(stpt, startPtrs[i]->course, startPtrs[i]->units);
                        }
                    }

                }
            }

        }

  if(sem.getUnits() == 0)
  {
    return;
  }else{
  cout << "complete" << endl;
  sem.print();
  for(int k = 0; k < sem.getSize(); k++){
    acc.addCourse(sem.getCourse(k)->courseNum,sem.getCourse(k)->course,sem.getCourse(k)->units);
  }
  sem.clearSem();
  startPtrs.clear();
  //vector<CatalogCourse *> newStartPtrs;
  //Semester sem1("Next Semester");
  getStartingPts(acc, cat, unitsCap, startPtrs);
  modFWAlgo(acc, cat, unitsCap, startPtrs, sem);
  }
}

int main()
{
  //initialization
    Catalog cmpe_cat("catalog_cmpe.txt", "prereqs_cmpe.txt", "coreqs_cmpe.txt", "CMPE");
    Catalog se_cat("catalog_se.txt", "prereqs_se.txt", "coreqs_se.txt", "CMPE");
    //create accounts
    Account accEmpCMPE("empty_cmpe.txt");
    Account accFrsCMPE("freshman_cmpe.txt");
    Account accJunCMPE("junior_cmpe.txt");
    Account accSenCMPE("senior_cmpe.txt");
    Account accEmpSE("empty_se.txt");
    Account accFrsSE("freshman_se.txt");
    Account accJunSE("junior_se.txt");
    Account accSenSE("senior_se.txt");

    Semester sem("Schedule");
    vector<CatalogCourse *> startPtrsCMPE;
    vector<CatalogCourse *> startPtrsSE;
    getStartingPts(accEmpCMPE, cmpe_cat, unitsCap, startPtrsCMPE);

    clock_t begin = clock();
    getStartingPts(accEmpCMPE, cmpe_cat, unitsCap, startPtrsCMPE);
    modFWAlgo(accEmpCMPE, cmpe_cat, unitsCap, startPtrsCMPE, sem);
    clock_t end = clock();
    double sec1 = double(end - begin) / CLOCKS_PER_SEC;
    //cout << elapsed_secs << endl;
    startPtrsCMPE.clear();
    cout << "------------\n";
    begin = clock();
    getStartingPts(accFrsCMPE, cmpe_cat, unitsCap, startPtrsCMPE);
    modFWAlgo(accFrsCMPE, cmpe_cat, unitsCap, startPtrsCMPE, sem);
    end = clock();
    double sec2 = double(end - begin) / CLOCKS_PER_SEC;
    //cout << elapsed_secs << endl;
    startPtrsCMPE.clear();
    cout << "------------\n";
    begin = clock();
    getStartingPts(accJunCMPE, cmpe_cat, unitsCap, startPtrsCMPE);
    modFWAlgo(accJunCMPE, cmpe_cat, unitsCap, startPtrsCMPE, sem);
    end = clock();
    double sec3 = double(end - begin) / CLOCKS_PER_SEC;
    //cout << elapsed_secs << endl;
    startPtrsCMPE.clear();
    cout << "------------\n";
    begin = clock();
    getStartingPts(accSenCMPE, cmpe_cat, unitsCap, startPtrsCMPE);
    modFWAlgo(accSenCMPE, cmpe_cat, unitsCap, startPtrsCMPE, sem);
    end = clock();
    double sec4 = double(end - begin) / CLOCKS_PER_SEC;
    //cout << elapsed_secs << endl;
    startPtrsCMPE.clear();
    cout << "------------\n";


    begin = clock();
    getStartingPts(accEmpSE, cmpe_cat, unitsCap, startPtrsSE);
    modFWAlgo(accEmpSE, cmpe_cat, unitsCap, startPtrsSE, sem);
    end = clock();
    double sec5 = double(end - begin) / CLOCKS_PER_SEC;
    //cout << elapsed_secs << endl;
    startPtrsSE.clear();
    cout << "------------\n";
    begin = clock();
    getStartingPts(accFrsSE, cmpe_cat, unitsCap, startPtrsSE);
    modFWAlgo(accFrsSE, cmpe_cat, unitsCap, startPtrsSE, sem);
    end = clock();
    double sec6 = double(end - begin) / CLOCKS_PER_SEC;
    //cout << elapsed_secs << endl;
    startPtrsSE.clear();
    cout << "------------\n";
    begin = clock();
    getStartingPts(accJunSE, cmpe_cat, unitsCap, startPtrsSE);
    modFWAlgo(accJunSE, cmpe_cat, unitsCap, startPtrsSE, sem);
    end = clock();
    double sec7 = double(end - begin) / CLOCKS_PER_SEC;
    //cout << elapsed_secs << endl;
    startPtrsSE.clear();
    cout << "------------\n";
    begin = clock();
    getStartingPts(accSenSE, cmpe_cat, unitsCap, startPtrsSE);
    modFWAlgo(accSenSE, cmpe_cat, unitsCap, startPtrsSE, sem);
    end = clock();
    double sec8 = double(end - begin) / CLOCKS_PER_SEC;
    //cout << elapsed_secs << endl;
    startPtrsSE.clear();

    cout << sec1 << endl;
    cout << sec2 << endl;
    cout << sec3 << endl;
    cout << sec4 << endl;
    cout << sec5 << endl;
    cout << sec6 << endl;
    cout << sec7 << endl;
    cout << sec8 << endl;

	return 0;
}

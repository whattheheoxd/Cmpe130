#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Catalog.h"
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
#include <iostream>

class Account
{
    public:
        Account(string); //initialize account info, read from file
        ~Account();
        void print();
        void addCourse(string, string, int, bool); //add to completedCourses
        bool completed(string); //returns true if course is completed

    private:
        fstream acc;	//text file for schedule
        string name;
        int studId;
        string major;
        string minor;
        vector<CatalogCourse*> completedCourses; //course history
        //vector<CatalogCourse> incompleteCourses;
};

#endif // ACCOUNT_H

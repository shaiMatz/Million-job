#pragma once
#include "checkFunction.h"

typedef struct employer
{
	char companyName[MAXNAME], Lname[MAXNAME], Fname[MAXNAME], email[MAXNAME],
		password1[MAXNAME], password2[MAXNAME], city[MAXNAME], answer[MAXNAME],
		phoneNumber[MAXNAME], jobDescription[MAXNAME];//all the candidate data
	int questionChoose;


}employer;


typedef struct job
{
	char* Jname[MAXNAME], Jrange[MAXNAME], Jcity[MAXNAME], Jtype[MAXNAME],
		Jdescription[MAXNAME], Jresponsibilities[MAXNAME],Jqualifications[MAXNAME], 
		Jsalary[MAXNAME], Jhours[MAXNAME], empEmail[MAXNAME];
	int serialNum;
}job;



int EmployerMenu(employer emp);
int jobAdd();
int jobEdit();
int editJobFromList(char* email);

job buildJob(int number);

employer employer_Registration();
employer loginE(char email[]);
employer resetPassword2(employer e);


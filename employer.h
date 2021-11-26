#pragma once
#include "checkFunction.h"

typedef struct employer
{
	char companyName[MAXNAME], Lname[MAXNAME], Fname[MAXNAME], email[MAXNAME],
		password1[MAXNAME], password2[MAXNAME], city[MAXNAME], answer[MAXNAME],
		phoneNumber[MAXNAME], jobDescription[MAXBUFFER];//all the employer data
	int questionChoose;


}employer;


typedef struct job
{
	char Jname[MAXNAME], Jrange[MAXBUFFER], Jcity[MAXNAME], Jtype[MAXNAME],
		Jdescription[MAXBUFFER], Jresponsibilities[MAXBUFFER], Jqualifications[MAXBUFFER],
		Jsalary[MAXNAME], Jhours[MAXNAME], empEmail[MAXNAME];
	int serialNum;
}job;


job buildJob(int number);
int EmployerMenu(employer emp);
int editProfileMenuEmp(employer emp);
int jobAdd(char* email);
int jobEdit(char* email);
int editJobFromList(char* email);
int deleteJob(char* email);
int printMyPublishedJobs(char* email);
int jobsOfferList(char* email);

employer editProfileEmp(employer emp, char* fileName, int ans);
employer employer_Registration();
employer loginE(char email[]);
employer resetPassword2(employer e);


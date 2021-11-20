#pragma once
#include "checkFunction.h"

typedef struct employer
{
	char companyName[MAXNAME], Lname[MAXNAME], Fname[MAXNAME], email[MAXNAME], password1[MAXNAME], password2[MAXNAME], city[MAXNAME], answer[MAXNAME], phoneNumber[MAXNAME], jobDescription[MAXNAME];//all the candidate data
	int questionChoose;


}employer;

employer employer_Registration();
employer loginE(char email[]);
employer resetPassword2(employer e);
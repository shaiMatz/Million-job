#pragma once
#include"checkFunction.h"


typedef struct candidate////yo????
{
	char ID[MAXNAME],Lname[MAXNAME], Fname[MAXNAME], email[MAXNAME], password1[MAXNAME], password2[MAXNAME], city[MAXNAME], answer[MAXNAME], phoneNumber[MAXNAME],CVname[MAXNAME], wantedjobs[MAXNAME];//all the candidate data
	int questionChoose;
	int month, day, year;
}candidate;

int CandidateMenu(candidate cand);
int CVFile(candidate cand);
candidate Candidate_Registration();
void searchEngine(candidate cand);
int editProfileMenu(candidate cand);
candidate loginC(char email[]);
candidate editProfile(candidate cand, char* fileName, int ans);
candidate resetPassword(candidate c);
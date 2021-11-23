#pragma once
#include "employer.h"
#include "candidate.h"
int Filtermenu(candidate cand);
void printJob(char* line);
int filtertown(candidate cand);
int filterjobhours(candidate cand);
int printall(candidate cand);
int pickAJob( candidate cand, job jobN);
int pickAFavJob(candidate cand, job jobN);
int filtersalary(candidate cand);
int choicemenu(candidate cand);
int filterjobtype(candidate cand);
#pragma once
#include "employer.h"
#include "candidate.h"
int Filtermenu(candidate cand);
void printJob(char* line);
int filtertown();
int filterjobhours();
int printall(candidate cand);
int pickAJob( candidate cand, job jobN);
int pickAFavJob(candidate cand, job jobN);
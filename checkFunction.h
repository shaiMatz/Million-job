
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include <fcntl.h>


#define MAXNAME 50
#define MAXBUFFER 2024

int CheckLower(char* city);
int IDCheck(char* ID);
int MailCheck(char* mail);
int PhoneCheck(char* phone);
int PasswordCheck(char* password);
int BirthCheck(int day, int month, int year);

//file functions
int findRightRow(char* fileName, char* email);//by email
int deleteline(char* fileName, int row);
int deleteJobLine(char* fileName, int row);
int findRightRowPass(char* fileName, char* pass);
const char* getfield(char* line, int column);
int ifExists(char* fileName, char* name, int column);
int sortFile(char* fileName, int column);
int sortFilefromendtostart(char* fileName, int column);
int lastSerial();
int findJobsubFile(char* fileName);
int deleteJobLineFromCAND_NAME_CSVfile(char* fileName, int serialNum);
int deleteFromSubAndFromPersonalcsvFile(char* fileName, int jobNumber);
int fevoritsAndAddDelete(int jobNumber);
int findRightRowSerial(char* fileName, char* serial);
int clearBuffer();

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include <fcntl.h>

#define MAXNAME 50
#define MAXBUFFER 2024


int IDCheck(char* ID);
int MailCheck(char* mail);
int PhoneCheck(char* phone);
int PasswordCheck(char* password);
int BirthCheck(int day, int month, int year);
//file functions
int findRightRow(char* fileName, char* email);
int deleteline(char* fileName, int row);
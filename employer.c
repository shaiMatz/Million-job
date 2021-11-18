#pragma once

#include"employer.h"

employer loginE(char email[])
{
	char* value, buffer[2024];
	int column = 0, row = 0, wantedRow = 1;
	employer newEmp;
	FILE* fp = fopen("Employer_DATA.csv", "r");
	if (!fp)
		printf("Can't open file\n");

	else
	{

		wantedRow = findRightRow("Employer_DATA.csv", email);
		if (wantedRow == 0)
		{
			printf("The email not found!");
			fclose(fp);
			return;
		}
		row = 0;
		rewind(fp);

		while (fgets(buffer, 1024, fp))
		{
			row++;
			column = 0;
			if (row == wantedRow)
			{
				value = strtok(buffer, ", ");
				while (value)
				{
					if (column == 0)
						strcpy(newEmp.companyName, value);
					if (column == 1)
						strcpy(newEmp.Fname, value);
					if (column == 2)
						strcpy(newEmp.Lname, value);
					if (column == 3)
						strcpy(newEmp.email, value);
					if (column == 4)
						strcpy(newEmp.password1, value);
					if (column == 5)
						strcpy(newEmp.city, value);
					if (column == 6)
						strcpy(newEmp.jobDescription, value);
					if (column == 7)
						strcpy(newEmp.phoneNumber, value);
					if (column == 8)
						newEmp.questionChoose = atoi(value);
					if (column == 9)
						strcpy(newEmp.answer, value);
					value = strtok(NULL, ", ");
					column++;
				}
			}
			else
				continue;
		}
	}
	fclose(fp);
	return newEmp;
}
employer employer_Registration()
{
	FILE* F = fopen("Employer_DATA.csv", "a+");
	employer newEmp;


	if (!F) {
		// Error in file opening
		printf("Can't open file\n");
		return;
	}

	// Asking user input for the
	// new record to be added
	getchar();
	printf("\nEnter company name:  \b");
	gets(newEmp.companyName);

	printf("\nEnter first name:  \b");
	scanf("%s", &newEmp.Fname);
	printf("\nEnter last name:  \b");
	scanf("%s", &newEmp.Lname);
	printf("\nEnter email address: (It will be your username)  \b");
	scanf("%s", &newEmp.email);
	while (MailCheck(newEmp.email) == 0)
	{
		printf("\nEnter email address: (It will be your username)  \b");
		scanf("%s", &newEmp.email);
	}
	printf("\nEnter password:  \b");
	scanf("%s", &newEmp.password1);
	while (PasswordCheck(newEmp.password1) == 0)
	{
		printf("\nEnter password:  \b");
		scanf("%s", &newEmp.password1);
	}
	printf("\nEnter your password again:  \b");
	scanf("%s", &newEmp.password2);
	while (strcmp(newEmp.password1, newEmp.password2))
	{
		printf("\nthe passwords are diffrents,enter your verfication password again:  \b");
		scanf("%s", &newEmp.password2);
	}
	getchar();
	printf("\nEnter your city name:  \b");
	gets(newEmp.city);
	printf("\nEnter phone number:  \b");
	scanf("%s", &newEmp.phoneNumber);
	while (PhoneCheck(newEmp.phoneNumber) == 0)
	{
		printf("\nEnter phone number:  \b");
		scanf("%s", &newEmp.phoneNumber);
	}
	getchar();
	printf("\nEnter some information about the company:  \n");
	gets(newEmp.jobDescription);

	printf("\nChoose your security question:(default qeustion is 1)\n");
	printf("press 1: What is your grandfather name from your father side? \n");
	printf("press 2: What is your pet name? \n");
	printf("press 3: What is the name of your high-school? \nyour choise:  \b");

	scanf("%d", &newEmp.questionChoose);
	printf("\nEnter your answer:  \b");
	scanf("%s", &newEmp.answer);

	// Saving data in file
	fprintf(F, "%s,%s,%s,%s,%s,%s,%s,%s,%d,%s\n", newEmp.companyName,
		newEmp.Fname, newEmp.Lname, newEmp.email, newEmp.password1, newEmp.jobDescription,
		newEmp.city, newEmp.phoneNumber, newEmp.questionChoose, newEmp.answer);
	fclose(F);
	system("cls");
	printf("\nNew Account added to record\n");

	return newEmp;

}

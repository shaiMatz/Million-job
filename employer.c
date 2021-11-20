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
	FILE* EmployerF = fopen("Employer_DATA.csv", "a+");
	employer newEmployer;


	if (!EmployerF)
	{
		// Error in file opening
		printf("Can't open file\n");
		return;
	}

	// Asking user input for the
	// new record to be added
	printf("\nEnter company name:  \b");
	gets(newEmployer.companyName);

	printf("\nEnter first name:  \b");
	scanf("%s", &newEmployer.Fname);
	printf("\nEnter last name:  \b");
	scanf("%s", &newEmployer.Lname);
	printf("\nEnter email address: (It will be your username)  \b");
	scanf("%s", &newEmployer.email);
	while (MailCheck(newEmployer.email) == 0)
	{
		printf("\nEnter email address: (It will be your username)  \b");
		scanf("%s", &newEmployer.email);
	}
	printf("\nEnter password:  \b");
	scanf("%s", &newEmployer.password1);
	while (PasswordCheck(newEmployer.password1) == 0)
	{
		printf("\nEnter password:  \b");
		scanf("%s", &newEmployer.password1);
	}
	printf("\nEnter your password again:  \b");
	scanf("%s", &newEmployer.password2);
	while (strcmp(newEmployer.password1, newEmployer.password2))
	{
		printf("\nthe passwords are diffrents,enter your verfication password again:  \b");
		scanf("%s", &newEmployer.password2);
	}
	getchar();
	printf("\nEnter your city name: (enter just in small letters) \b");
	gets(newEmployer.city);
	while (CheckLower(newEmployer.city) == 0)
	{
		gets(newEmployer.city);
	}
	printf("\nEnter phone number:  \b");
	scanf("%s", &newEmployer.phoneNumber);
	while (PhoneCheck(newEmployer.phoneNumber) == 0)
	{
		printf("\nEnter phone number:  \b");
		scanf("%s", &newEmployer.phoneNumber);
	}
	getchar();
	printf("\nEnter some information about the company:  \n");
	gets(newEmployer.jobDescription);

	printf("\nChoose your security question:(default qeustion is 1)\n");
	printf("press 1: What is your grandfather name from your father side? \n");
	printf("press 2: What is your pet name? \n");
	printf("press 3: What is the name of your high-school? \nyour choise:  \b");

	scanf("%d", &newEmployer.questionChoose);
	getchar();
	printf("\nEnter your answer:  \b");
	gets(newEmployer.answer);

	// Saving data in file
	fprintf(EmployerF, "%s,%s,%s,%s,%s,%s,%s,%s,%d,%s\n", newEmployer.companyName,
		newEmployer.Fname, newEmployer.Lname, newEmployer.email, newEmployer.password1, newEmployer.jobDescription,
		newEmployer.city, newEmployer.phoneNumber, newEmployer.questionChoose, newEmployer.answer);
	fclose(EmployerF);
	system("cls");
	printf("\nNew Account added to record!\n");
	return newEmployer;

}

int EmployerMenu(employer emp)
{
	int run = 0;
	int choice = '0';
	while (run != -1)
	{
		printf("----Wellcome dear %s---- \n",emp.Fname);
		printf("Employer Menu :\n");
		printf("Press 1 to Search engine.\n");// signed as a same candidate search engine in the requirments...
		printf("Press 2 to Add,Edit,Delete jobs.\n");
		printf("Press 3 to List of my jobs offers.\n");
		printf("Press 4 to Edit profile.\n");
		printf("Press 5 to delete profile.\n");
		printf("Press 6 to Candidate Search.\n");
		printf("Press 7 to exit.\n\nchoice : ");
		scanf("%c", &choice);
		switch (choice)
		{
		case '1': {
			//searchEngine();
			break;
		}
		case '2':
		{
			jobEdit();// inside function switch cases between 3 cases (edit,add,delete)
			break;
		}
		case '3':
		{
			//jobsOfferList();//printing list of jobs and details,viewing optional candidates for specific jobs , and option to delete the job
			break;
		}
		case '4':
		{
			//empProfilEdit();// not the same  profile for the employer...
		}
		case '5': {
			//deleteProfile();
		}
		case '6':
		{
			run = -1;
			//candidateSearch();// candidate searching by age/type/working area
		}
		case '7':
		{
			//logoutFunc();// Logout Function
		}

		default:
		{
			system("cls");
			printf("wrong Input Please Choose between 1-7 \n");
		}
		}
	}
	return main();
}
employer resetPassword2(employer e)
{
	char securityAnswer[MAXNAME];
	int run = 0;
	int run2 = 0;
	char temp[MAXNAME];
	strcpy(temp, e.password1);
	while (run == 0)
	{
		printf("\nTo reset you're password, enter you're security answer : ");
		scanf("%s", &securityAnswer);
		if (strcmp(e.answer, securityAnswer) == 0)
		{
			while (run2 == 0)
			{
				printf("Enter you're new password twice :\nFirst time : ");
				scanf("%s", &e.password1);
				while (PasswordCheck(e.password1) == 0)
				{
					printf("Enter valid password : ");
					scanf("%s", &e.password1);
				}
				if (strcmp(temp, e.password1) != 0)
				{
					printf("Second Time : ");
					scanf("%s", &e.password2);
					if (strcmp(e.password1, e.password2) != 0)
					{
						printf("Passwords are different, try again : ");
					}
					else
					{
						printf("Done !\n");
						run2 = 1;
						return e;
					}
				}
				if (strcmp(temp, e.password1) == 0)
					printf("the new password can be same as the old one, try again !\n");
			}
		}
		else
		{
			printf("You're security answer doesn't match, try again !\n");
		}
	}

}

int jobEdit()// inside function switch cases between 3 cases (edit,add,delete)
{
	int run = 0;
	char choice = '0';
	
	while (run != -1)
	{
		printf("1) Press 1 to add a job.\n");
		printf("2) Press 2 to Edit a job.\n");
		printf("3) Press 3 to delete a job.\n");
		printf("4) Press 4 to exit.\n\nchoice : ");
		scanf("%c", &choice);
		switch (choice) 
		{
		case '1':
		{
			jobAdd();
			break;
		}
		case '2':
		{
			break;
		}
		case '3':
		{
			break;
		}
		case '4':
		{
			system("cls");
			run = -1;
			getchar();
			break;
		}
		default:
		{
			system("cls");
			printf("wrong Input Please Choose between 1-4 \n");
		}
		}

	}

}
int jobAdd()
{

	char* Jname[MAXNAME], Jrange[MAXNAME], Jtype[MAXNAME], Jdescription[MAXNAME], Jresponsibilities[MAXNAME], Jqualifications[MAXNAME], Jsalary[MAXNAME], Jhours[MAXNAME];
	

	FILE* JobF = fopen("JOB_LIST_DATA.csv", "a+");


	if (!JobF) {
		// Error in file opening
		printf("Can't open file\n");
		return;
	}


	printf("\nEnter the job name: \n");
	gets(Jname);
	printf("\nEnter the job range: \n");
	gets(Jrange);
	
	printf("\nEnter the job type(full time/part time): \n");
	gets(Jtype);
	printf("\nEnter the job description: \n");
	gets(Jdescription);
	
	printf("\nEnter the job responsibilities: \n");
	gets(Jresponsibilities);
	
	printf("\nEnter the job qualifications: \n");
	gets(Jqualifications);
	
	printf("\nEnter the job salary: \n");
	gets(Jsalary);
	printf("\nEnter the job hours: \n");
	gets(Jhours);

	// Saving data in file
	fprintf(JobF, "%s,%s,%s,%s,%s,%s,%s,%s\n", Jname,
		Jrange, Jtype, Jdescription, Jresponsibilities, Jqualifications,
		Jsalary, Jhours);
	fclose(JobF);
	system("cls");
	printf("\nNew job added to record\n");
	return 0;


}









//printf("\nEnter your job qualifications:  \n");
//while (scanf("%[^\n]%*c", jobQ) == 1)
//{
//	strcat(jobQualifications, " ");
//	strcat(jobQualifications, jobQ);
//}
